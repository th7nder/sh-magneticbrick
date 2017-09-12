//
//  BacteriaBlue.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "BacteriaBlue.hpp"



BacteriaBlue::BacteriaBlue()
{
    
}

BacteriaBlue::~BacteriaBlue()
{
    
}

BacteriaBlue* BacteriaBlue::create(GameHandler* handler)
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


bool BacteriaBlue::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void BacteriaBlue::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    velocity.x = pixelsToMeters(props["vX"].asFloat());
    velocity.y = pixelsToMeters(props["vY"].asFloat());
    angle = CC_RADIANS_TO_DEGREES(atanf(velocity.x / velocity.y));
}


void BacteriaBlue::addSprite()
{
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_bacteriablue"]);
    //sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setCascadeOpacityEnabled(true);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    addChild(sprite);
    sprite->setRotation(angle);
}


void BacteriaBlue::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto shape = new b2PolygonShape();
    shape->SetAsBox(pixelsToMeters(size.width), pixelsToMeters(size.height), b2Vec2(pixelsToMeters(25), pixelsToMeters(50)), CC_DEGREES_TO_RADIANS(180.0f - angle));
    body->CreateFixture(createFixture(shape));
    body->SetType(b2_kinematicBody);
    
    
}

void BacteriaBlue::launch()
{
    CCLOG("launching blue");
    body->SetLinearVelocity(velocity);
}

void BacteriaBlue::savePreviousStates()
{
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
}

void BacteriaBlue::interpolate(float alpha)
{
    Vec2 target(metersToPixels(lerp(previousPosition.x, body->GetPosition().x, alpha)), metersToPixels(lerp(previousPosition.y, body->GetPosition().y, alpha)));
    setPosition(target);
}
