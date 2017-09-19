//
//  Player.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#include "Player.hpp"

#include "Level.hpp"
#include "Star.hpp"

Player::Player(Skin skin, LevelFollower* follower, Walls* walls) :
rightBody(nullptr),
rightSprite(nullptr),
forceTouch(false),
speed(0.0),
startLeftPos(0.0f),
startRightPos(0.0f),
startTouchPosition(Vec2::ZERO),
playerSize(Vec2::ZERO),
leftBarrier(nullptr),
previousRightPosition(Vec2::ZERO),
rightBarrier(nullptr),
isTouching(false),
inTeleport(false),
modifierGravity(false),
levelFollower(follower),
walls(walls),
halfPlayerWidth(0.0)
{
    currentTeleportTarget = "";
    
    listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(self::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(self::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(self::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(self::onTouchesCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    currentSkin = skin;

}

Player::~Player()
{
    rightBody->GetWorld()->DestroyBody(rightBody);
    rightBarrier->GetWorld()->DestroyBody(rightBarrier);
    leftBarrier->GetWorld()->DestroyBody(leftBarrier);
    _eventDispatcher->removeEventListener(listener);
}

int Player::getZ() const
{
    return 30;
}

Sprite* Player::getRightSprite()
{
    return rightSprite;
}



// setCurrentPlayerSpeed, tutorialShit, stars, gravity
void Player::setProperties(ValueMap &props)
{
    super::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "Player -> initialSpeed isNull");
    speed = (props["initialSpeed"].asFloat());
    
    setContentSize(Size(_director->getVisibleSize().width, _contentSize.height));
    setPositionX(_contentSize.width / 2);
    
}


// separate Player into two Players or no? think about it
void Player::addSprite()
{
    CCLOG("OMG: %s", currentSkin.getLeftPath().c_str());
    sprite = Sprite::create(currentSkin.getLeftPath());
    playerSize = sprite->getContentSize();
    halfPlayerWidth = playerSize.width / 2;
    startLeftPos = getPositionX() - playerSize.width / 2;
    sprite->setPositionX(startLeftPos);
    sprite->setPositionY(playerSize.width / 2);
    addChild(sprite);
    
    previousPosition = sprite->getPosition();
    
    rightSprite = Sprite::create(currentSkin.getRightPath());
    startRightPos = sprite->getPositionX() + sprite->getContentSize().width;
    rightSprite->setPositionX(startRightPos);
    rightSprite->setPositionY(playerSize.width / 2);
    addChild(rightSprite);
    
    previousRightPosition = rightSprite->getPosition();
    

}

void Player::initPhysics(b2World* world)
{
    float y = getPositionY();
    body = world->CreateBody(createBody(Vec2(sprite->getPositionX(), y)));
    body->CreateFixture(createFixture(createRectangularShape(playerSize)));
    
    rightBody = world->CreateBody(createBody(Vec2(rightSprite->getPositionX(),  y)));
    rightBody->CreateFixture(createFixture(createRectangularShape(playerSize)));
    
    leftBarrier = createBarrier(world, sprite->getPositionX() + playerSize.width / 2, y);
    rightBarrier = createBarrier(world, rightSprite->getPositionX() - playerSize.width / 2, y);
    
    
    body->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    rightBody->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
    previousRightPosition = Vec2(rightBody->GetPosition().x, rightBody->GetPosition().y);
}

void Player::savePreviousStates()
{
    previousPosition = Vec2(metersToPixels(body->GetPosition().x), metersToPixels(body->GetPosition().y));
    previousRightPosition = Vec2(metersToPixels(rightBody->GetPosition().x), metersToPixels(rightBody->GetPosition().y));
}

void Player::interpolate(float alpha)
{
    setPositionY(lerp(previousPosition.y, metersToPixels(body->GetPosition().y), alpha));
    sprite->setPositionX(lerp(previousPosition.x, metersToPixels(body->GetPosition().x), alpha));
    rightSprite->setPositionX(lerp(previousRightPosition.x, metersToPixels(rightBody->GetPosition().x), alpha));
    
}


b2BodyDef* Player::createBody(const Vec2& pos)
{
    b2BodyDef* body = LevelObject::createBody(pos);
    body->type = b2_dynamicBody;
    body->bullet = true;
    return body;
}

b2FixtureDef* Player::createFixture(b2Shape *shape)
{
    b2FixtureDef* fixture = LevelObject::createFixture(shape);
    fixture->filter.categoryBits = kFilterCategoryPlayer;
    fixture->filter.maskBits = kFilterCategorySolidObject | kFilterCategoryLevel | kFilterCategoryNonSolidObject;
    fixture->friction = 0.0;
    fixture->restitution = 0.0;
    fixture->density = 0.0f;
    return fixture;
}

b2Body* Player::createBarrier(b2World* world, float x, float y)
{
    auto bodyDef = createBody(Vec2(x, y));
    bodyDef->type = b2_kinematicBody;
    

    auto ret = world->CreateBody(bodyDef);
    auto shape = new b2EdgeShape;
    shape->Set(b2Vec2(0, -3), b2Vec2(0, 3));
    auto fixture = super::createFixture(shape);
    fixture->filter.categoryBits = kFilterCategoryLevel;
    ret->CreateFixture(fixture);
    ret->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    ret->SetBullet(true);
    return ret;
}


void Player::launch()
{
    
}



void Player::setVelocities(float v)
{
    v = pixelsToMeters(v);    
    body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, v));
    rightBody->SetLinearVelocity(b2Vec2(rightBody->GetLinearVelocity().x, v));
    if(leftBarrier != nullptr)
    {
        leftBarrier->SetLinearVelocity(b2Vec2(0, v));
        rightBarrier->SetLinearVelocity(b2Vec2(0, v));
    }
    if(walls != nullptr)
    {
        walls->getRightBody()->SetLinearVelocity(b2Vec2(0, v));
        walls->getBody()->SetLinearVelocity(b2Vec2(0, v));
    }
    if(levelFollower != nullptr)
    {
        levelFollower->getBody()->SetLinearVelocity(b2Vec2(0, -v));
    }

}

void Player::disableCollisionWithSolids()
{
    auto filter = body->GetFixtureList()->GetFilterData();
    filter.maskBits = kFilterCategoryLevel | kFilterCategoryNonSolidObject;
    body->GetFixtureList()->SetFilterData(filter);
    rightBody->GetFixtureList()->SetFilterData(filter);
}

void Player::enableCollisionWithSolids()
{
    auto filter = body->GetFixtureList()->GetFilterData();
    filter.maskBits = kFilterCategorySolidObject | kFilterCategoryLevel | kFilterCategoryNonSolidObject;
    body->GetFixtureList()->SetFilterData(filter);
    rightBody->GetFixtureList()->SetFilterData(filter);
}

bool Player::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    if(other->getDescription() == "TeleportIn")
    {
        if(!inTeleport)
        {
            float teleportY = other->getBody()->GetPosition().y - pixelsToMeters(other->getContentSize().height / 2);
            float brickY = body->GetPosition().y + pixelsToMeters(playerSize.height / 2);
            if(std::abs(brickY - teleportY) <= 0.15f)
            {
                auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
                sae->playEffect(Globals::resources["effect_teleport_in"].c_str());

                inTeleport = true;
                sprite->runAction(FadeOut::create(0.3));
                rightSprite->runAction(FadeOut::create(0.3));
                
                setVelocities(speed * 4);
                disableCollisionWithSolids();
                currentTeleportTarget = ((TeleportIn*)other)->target;
            }

        }
    } else if(other->getDescription() == "TeleportOut")
    {
        if(inTeleport && (currentTeleportTarget == "" || other->getName() == currentTeleportTarget))
        {
            inTeleport = false;
            auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
            sae->playEffect(Globals::resources["effect_teleport_out"].c_str());
            sprite->runAction(FadeIn::create(0.3));
            rightSprite->runAction(FadeIn::create(0.3));
            setVelocities(speed);
            enableCollisionWithSolids();
        }
    } else if(other->getDescription() == "Star")
    {
        if(!inTeleport)
        {
            //other->remove = true;
            //gameHandler->onStarCollected(((Star*)other)->getNumber());
        }
        
    }
    return false;
}




// refactor
void Player::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    startTouchPosition = touches[0]->getStartLocation();
    force = 0.0;
    
    auto gameHandler = GameHandler::sharedInstance();
    if(gameHandler->getGameState() == GameHandler::GameState::ReadyToPlay)
    {
        tempStartPos = getPositionY();
        gameHandler->setGameState(GameHandler::GameState::Playing);
        setVelocities(speed);
        
        if(getOpacity() == 128)
        {
            auto func = CallFunc::create([this](){
                if(!this->inTeleport)
                {
                    this->enableCollisionWithSolids();
                }

                this->setOpacity(255);
                this->setCascadeOpacityEnabled(false);
            });
            auto seq = Sequence::create(DelayTime::create(2.4),
                                        FadeTo::create(0.05, 0), DelayTime::create(0.05), FadeTo::create(0.05, 129), DelayTime::create(0.05),
                                        FadeTo::create(0.05, 0), DelayTime::create(0.05), FadeTo::create(0.05, 129), DelayTime::create(0.05),
                                        FadeTo::create(0.05, 0), DelayTime::create(0.05), FadeTo::create(0.05, 129), DelayTime::create(0.05),
                                        FadeTo::create(0.05, 0), DelayTime::create(0.05), FadeTo::create(0.05, 255), DelayTime::create(0.05),
                                        func, NULL);
            
            runAction(seq);
        }

    }
}

void Player::resetSpriteY()
{
    setCascadeOpacityEnabled(true);
    setVisible(true);
    sprite->setRotation(0);
    rightSprite->setRotation(0);
    interpolate(0);
    disableCollisionWithSolids();
    sprite->setPositionY(playerSize.width / 2);
    rightSprite->setPositionY(playerSize.width / 2);
    setOpacity(128);
    setVelocities(speed);
    
    rightBody->SetTransform(b2Vec2(rightBody->GetPosition().x, body->GetPosition().y), 0);
    

}

void Player::updateBricksSpacing()
{
    return;
    if(inTeleport) return;
    auto width = _contentSize.width;
    
    float force;
    if(modifierGravity)
    {
        force = 1.0 - this->force;
    }
    else
    {
        force = this->force;
    }
    
    auto leftBarrierPos = pixelsToMeters(startLeftPos - ((startLeftPos - halfPlayerWidth) * force));
    auto previousBrickXVel = body->GetLinearVelocity().x;
    auto previousRightBrickXVel = rightBody->GetLinearVelocity().x;
    auto leftBrickPos = body->GetPosition().x;
    auto rightBarrierPos = pixelsToMeters(startRightPos + (width - halfPlayerWidth - startRightPos) * force);
    
    float brickVelocity = -64.0f;
    float rightBrickVelocity = 64.0f;
    if(leftBrickPos <= leftBarrierPos) // from left to right
    {
        brickVelocity = -brickVelocity;
        rightBrickVelocity = -rightBrickVelocity;
        
        leftBarrierPos += halfPlayerWidth;
        rightBarrierPos -= halfPlayerWidth;
    } else if(leftBrickPos > leftBarrierPos) // from right to left
    {
        leftBarrierPos -= halfPlayerWidth;
        rightBarrierPos += halfPlayerWidth;
    }
    

    
    rightBarrier->SetTransform(b2Vec2(rightBarrierPos, rightBarrier->GetPosition().y), 0.0);
    leftBarrier->SetTransform(b2Vec2(leftBarrierPos, leftBarrier->GetPosition().y), 0.0);
        

    if(previousBrickXVel != brickVelocity)
    {
        body->ApplyLinearImpulse(b2Vec2(brickVelocity * (1 + std::abs(previousBrickXVel / brickVelocity)), 0), body->GetWorldCenter(), true);
    }
        
    if(previousRightBrickXVel != rightBrickVelocity)
    {
        rightBody->ApplyLinearImpulse(b2Vec2(rightBrickVelocity * (1 + std::abs(previousRightBrickXVel / rightBrickVelocity)), 0), rightBody->GetWorldCenter(), true);
    }
    

}

void Player::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    Touch* touch = nullptr;
    if((touch = touches[0]))
    {
        if(forceTouch)
        {
            force = touch->getCurrentForce() / touch->getMaxForce();
        }
        else
        {
            auto touchPos = touch->getLocation();
            if(touchPos.x > startTouchPosition.x)
            {
                float difference = (touchPos.x - startTouchPosition.x);
                static const float base = 640 / 2.5;
                force = difference / base;
                if(force >= 1.0)
                {
                    startTouchPosition.x += touchPos.x - (startTouchPosition.x + base);
                    force = 1.0;
                }
            } else {
                startTouchPosition = touchPos;
                force = 0.0;
            }
        }
        updateBricksSpacing();
        
    }
}

void Player::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    force = 0.0;
    updateBricksSpacing();
}

void Player::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
{
    force = 0.0;
    updateBricksSpacing();
}


void Player::dieAnimation()
{
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_brick_destroy"].c_str());
    
    ccBezierConfig bezier;
    auto pos1 = rightSprite->getPosition();
    bezier.controlPoint_1 = pos1;
    
    Vec2 pos2 = rightSprite->getPosition();
    pos2.x += 50.0;
    pos2.y += 300.0;
    bezier.controlPoint_2 = pos2;

    
    Vec2 pos3 = rightSprite->getPosition();
    pos3.x += 100.0;
    pos3.y -= 500.0;
    bezier.endPosition = pos3;
    
    rightSprite->runAction(Spawn::create(BezierTo::create(0.5, bezier), RotateBy::create(0.5, Vec3(0, 0, 90)), nullptr));
    
    ccBezierConfig bezierLeft;
    pos1 = sprite->getPosition();
    bezierLeft.controlPoint_1 = pos1;
    
    pos2 = sprite->getPosition();
    pos2.x -= 50.0;
    pos2.y += 270.0;
    bezierLeft.controlPoint_2 = pos2;
    
    pos3 = sprite->getPosition();
    pos3.x -= 100.0;
    pos3.y -= 500.0;
    bezierLeft.endPosition = pos3;
    sprite->runAction(Spawn::create(BezierTo::create(0.5, bezierLeft), RotateBy::create(0.5, Vec3(0, 0, -90)), nullptr));
    
    runAction(Sequence::create(DelayTime::create(0.55), CallFunc::create([this]() {this->setVisible(false);}), nullptr));
}
