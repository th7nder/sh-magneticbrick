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

Player::Player() :
rightBody(nullptr),
rightSprite(nullptr),
speed(0.0),
startLeftPos(0.0f), startRightPos(0.0f), startTouchPosition(Vec2::ZERO), playerSize(Vec2::ZERO), leftBarrier(nullptr),previousRightPosition(Vec2::ZERO),rightBarrier(nullptr), isTouching(false), inTeleport(false), nearSwitch(0)
{
    currentTeleportTarget = "";
}

Player::~Player()
{
    rightBody->GetWorld()->DestroyBody(rightBody);
    rightBarrier->GetWorld()->DestroyBody(rightBarrier);
    leftBarrier->GetWorld()->DestroyBody(leftBarrier);
    _eventDispatcher->removeEventListener(listener);
}



double Player::getCurrentTimeInSeconds()
{
    static struct timeval currentTime;
    gettimeofday(&currentTime, nullptr);
    return (currentTime.tv_sec) + (currentTime.tv_usec / 1000000.0);
}


Player* Player::create(GameHandler* handler, Walls* w, LevelFollower* lf)
{
    self* ret = new (std::nothrow) self();
    if (ret && ret->init(handler, w, lf))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool Player::init(GameHandler* handler, Walls* w, LevelFollower* lf)
{
    if(!super::init(gameHandler)) return false;
    gameHandler = handler;
    walls = w;
    levelFollower = lf;
    listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(self::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(self::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(self::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(self::onTouchesCancelled, this);
    

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

// setCurrentPlayerSpeed
void Player::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "initialSpeed was not set in map!");
    speed = (props["initialSpeed"].asFloat());
    tutorialPlayer = true;
    if(props["tutorial"].isNull())
    {
        gameHandler->setCurrentPlayerSpeed(speed);
        gameHandler->setPlayerStartY(getPositionY());
        tutorialPlayer = false;
    }
}

void Player::addSprite()
{
    setContentSize(Size(ownVisibleSize.width, getContentSize().height));
    
    auto currentSkin = gameHandler->getCurrentSkin();
    sprite = Sprite::create(currentSkin.getLeftPath());

    playerSize = sprite->getContentSize();
    startLeftPos = getPositionX() - playerSize.width / 2;
    
    sprite->setPositionX(startLeftPos);
    sprite->setPositionY(playerSize.width / 2);
    addChild(sprite);
    
    rightSprite = Sprite::create(currentSkin.getRightPath());
    startRightPos = sprite->getPositionX() + sprite->getContentSize().width;
    rightSprite->setPositionX(startRightPos);
    rightSprite->setPositionY(playerSize.width / 2);
    addChild(rightSprite);
    
    setPositionX(ownVisibleSize.width / 2);
    


}


b2BodyDef* Player::createBody(float x, float y)
{
    b2BodyDef* body = LevelObject::createBody(x, y);
    body->type = b2_dynamicBody;
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
    auto bodyDef = createBody(x, y);
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

b2Body* Player::createDestroyer(b2World* world, float x, float y)
{
    auto bodyDef = createBody(x, y);
    bodyDef->type = b2_kinematicBody;
    
    
    auto ret = world->CreateBody(bodyDef);
    auto shape = new b2EdgeShape;
    shape->Set(b2Vec2(0, -1), b2Vec2(0, 1));
    auto fixture = super::createFixture(shape);
    fixture->filter.categoryBits = kFilterCategorySolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    ret->CreateFixture(fixture);
    ret->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    ret->SetBullet(true);
    return ret;
}

void Player::initPhysics(b2World* world)
{
    
    
    body = world->CreateBody(createBody(sprite->getPositionX(), getPositionY()));
    body->CreateFixture(createFixture(createRectangularShape(playerSize.width, playerSize.height)));
    body->SetBullet(true);
    leftBarrier = createBarrier(world, sprite->getPositionX() + playerSize.width / 2, getPositionY());
    
    rightBody = world->CreateBody(createBody(rightSprite->getPositionX(),  getPositionY()));
    rightBody->CreateFixture(createFixture(createRectangularShape(playerSize.width, playerSize.height)));
    rightBody->SetBullet(true);
    
    rightBarrier = createBarrier(world, rightSprite->getPositionX() - playerSize.width / 2, getPositionY());

    body->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    rightBody->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
    previousRightPosition = Vec2(rightBody->GetPosition().x, rightBody->GetPosition().y);
}

void Player::setVelocities(float v)
{

    gameHandler->setCurrentPlayerSpeed(v);
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
            float teleportY = other->getBody()->GetPosition().y - pixelsToMeters(other->height / 2);
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
            other->remove = true;
            gameHandler->onStarCollected(((Star*)other)->getNumber(), other->getPositionX());
            
        }
        
    }
    return false;
}


bool Player::OnContactEnd(LevelObject *other)
{
    
    
    return false;
}


void Player::savePreviousStates()
{
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
    previousRightPosition = Vec2(rightBody->GetPosition().x, rightBody->GetPosition().y);
}

void Player::interpolate(float alpha)
{
    if(gameHandler->getGameState() == GameHandler::GameState::Tutorial && !tutorialPlayer) return;
    
    setPositionY(metersToPixels(lerp(previousPosition.y, body->GetPosition().y, alpha)));
    sprite->setPositionX(metersToPixels(lerp(previousPosition.x, body->GetPosition().x, alpha)));
    rightSprite->setPositionX(metersToPixels(lerp(previousRightPosition.x, rightBody->GetPosition().x, alpha)));
    if(!isTouching && !inTeleport)
    {
        updateBricksSpacing();
    }
    
}



void Player::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    
    if(gameHandler->getGameState() == GameHandler::GameState::Tutorial && !tutorialPlayer) return;
    isTouching = true;
    startTouchPosition = touches[0]->getStartLocation();
    force = 0.0;
    if(gameHandler->getGameState() == GameHandler::GameState::ReadyToPlay)
    {
        tempTime = getCurrentTimeInSeconds();
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
    if(gameHandler->getGameState() == GameHandler::GameState::Tutorial && !tutorialPlayer) return;
    

    if(inTeleport) return;
    auto width = getContentSize().width;
    float force;
    if(gameHandler->getGravity())
    {
        force = 1.0 - this->force;
    }
    else
    {
        force = this->force;
    }
    
    auto leftBarrierPos = pixelsToMeters(startLeftPos - ((startLeftPos  - playerSize.width / 2) * force));
    auto previousBrickXVel = body->GetLinearVelocity().x;
    auto previousRightBrickXVel = rightBody->GetLinearVelocity().x;
    auto leftBrickPos = body->GetPosition().x;
    auto halfPlayerWidth = pixelsToMeters(playerSize.width / 2);
    auto rightBarrierPos = pixelsToMeters(startRightPos + (width - (playerSize.width / 2) - startRightPos) * force);
    
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
    if(gameHandler->getGameState() == GameHandler::GameState::Tutorial && !tutorialPlayer) return;
    for(const auto& touch : touches)
    {
        if(gameHandler->getForceTouch())
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
                if(!nearSwitch)
                {
                    force = difference / base;
                }
                
                
                if(force >= 1.0)
                {
                    startTouchPosition.x += touchPos.x - (startTouchPosition.x + base);
                    force = 1.0;
                } else if(nearSwitch)
                {
                    float currForce = difference / base;

                    CCLOG("nearSwitch %d currForce - force %f", nearSwitch, currForce - force);
                    if((nearSwitch == 1 && currForce > force) || (currForce == 2 && currForce < force))
                    {
                        float deltaForce = currForce - force;
                        startTouchPosition.x += base * deltaForce;
                        //CCLOG("upgrading force by: %f", base * deltaForce);
                        //CCLOG("previous force: %f curr force: %f", force, (touchPos.x - startTouchPosition.x) / base);
                        
                        force = (touchPos.x - startTouchPosition.x) / base;
                    }
                    else
                    {
                        nearSwitch = 0;
                        force = currForce;
                    }
                
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
    if(gameHandler->getGameState() == GameHandler::GameState::Tutorial && !tutorialPlayer) return;
    isTouching = false;
    force = 0.0;
    updateBricksSpacing();
}

void Player::onTouchesCancelled(const std::vector<Touch*>& touches, Event* event)
{
    if(gameHandler->getGameState() == GameHandler::GameState::Tutorial && !tutorialPlayer) return;
    isTouching = false;
    force = 0.0;
    updateBricksSpacing();
}


void Player::die()
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
