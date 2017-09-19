//
//  BacteriaPink.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "BacteriaPink.hpp"



USING_NS_CC;
BacteriaPink::BacteriaPink()
{
    
}

BacteriaPink::~BacteriaPink()
{
    
}


void BacteriaPink::setProperties(ValueMap &props)
{
    super::setProperties(props);
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
    body = world->CreateBody(createBody(getPosition()));
    body->CreateFixture(createFixture(createCircleShape(size.width)));
    
    body->SetType(b2_kinematicBody);
    //body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(180.0f - angle));
    
    
}

void BacteriaPink::launch()
{
    CCLOG("launching pink");
    body->SetLinearVelocity(velocity);
}

