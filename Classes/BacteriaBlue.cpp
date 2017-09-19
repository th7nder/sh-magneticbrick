//
//  BacteriaBlue.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "BacteriaBlue.hpp"

USING_NS_CC;

BacteriaBlue::BacteriaBlue()
{
    
}

BacteriaBlue::~BacteriaBlue()
{
    
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
    body = world->CreateBody(createBody(getPosition()));
    auto shape = new b2PolygonShape();
    shape->SetAsBox(pixelsToMeters(size.width), pixelsToMeters(size.height), b2Vec2(pixelsToMeters(25), pixelsToMeters(50)), CC_DEGREES_TO_RADIANS(180.0f - angle));
    body->CreateFixture(createFixture(shape));
    body->SetType(b2_kinematicBody);
    
    
}

void BacteriaBlue::launch()
{
    body->SetLinearVelocity(velocity);
}

