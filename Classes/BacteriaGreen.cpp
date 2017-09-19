//
//  BacteriaGreen.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "BacteriaGreen.hpp"


USING_NS_CC;
BacteriaGreen::BacteriaGreen()
{
    
}

BacteriaGreen::~BacteriaGreen()
{
    
}


void BacteriaGreen::setProperties(ValueMap &props)
{
    super::setProperties(props);
    velocity.x = pixelsToMeters(props["vX"].asFloat());
    velocity.y = pixelsToMeters(props["vY"].asFloat());
    angle = CC_RADIANS_TO_DEGREES(atanf(velocity.x / velocity.y));
}


void BacteriaGreen::addSprite()
{
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_bacteriagreen"]);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    sprite->setCascadeOpacityEnabled(true);
    addChild(sprite);
    sprite->setRotation(angle);
}


void BacteriaGreen::initPhysics(b2World *world)
{
    super::initPhysics(world);
    body->SetType(b2_kinematicBody);
    body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(180.0f - angle));
    
    
}

void BacteriaGreen::launch()
{
    body->SetLinearVelocity(velocity);
    CCLOG("launching green");
}

