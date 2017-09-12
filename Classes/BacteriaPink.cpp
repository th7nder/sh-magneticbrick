//
//  BacteriaPink.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "BacteriaPink.hpp"





BacteriaPink::BacteriaPink()
{
    
}

BacteriaPink::~BacteriaPink()
{
    
}

BacteriaPink* BacteriaPink::create(GameHandler* handler)
{
    self* ret = new (std::nothrow) self();
    if (ret && ret->init(handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool BacteriaPink::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void BacteriaPink::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);

    velocity.x = pixelsToMeters(props["vX"].asFloat());
    velocity.y = pixelsToMeters(props["vY"].asFloat());
    angle = CC_RADIANS_TO_DEGREES(atanf(velocity.x / velocity.y));
}


void BacteriaPink::addSprite()
{
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_bacteriapink"]);
    //sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    sprite->setCascadeOpacityEnabled(true);
    addChild(sprite);
    sprite->setRotation(angle);
}


void BacteriaPink::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    body->CreateFixture(createFixture(createCircleShape(size.width)));
    
    body->SetType(b2_kinematicBody);
    //body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(180.0f - angle));
    
    
}

void BacteriaPink::launch()
{
    CCLOG("launching pink");
    body->SetLinearVelocity(velocity);
}



void BacteriaPink::savePreviousStates()
{
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
    
    //float targetX = metersToPixels(body->GetPosition().x);
   // float targetY = metersToPixels(body->GetPosition().y);
   // setPosition(targetX, targetY);
}

void BacteriaPink::interpolate(float alpha)
{
    Vec2 target(metersToPixels(lerp(previousPosition.x, body->GetPosition().x, alpha)), metersToPixels(lerp(previousPosition.y, body->GetPosition().y, alpha)));
    setPosition(target);
}
