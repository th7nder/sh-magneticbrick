//
//  Bullet.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#include "Bullet.hpp"

USING_NS_CC;
Bullet::Bullet()
{
    
}

Bullet::~Bullet()
{
    
}



void Bullet::setProperties(ValueMap &props)
{
    super::setProperties(props);
    velocity.x = pixelsToMeters(props["vX"].asFloat());
    velocity.y = pixelsToMeters(props["vY"].asFloat());
    angle = CC_RADIANS_TO_DEGREES(atanf(velocity.x / velocity.y));
}


void Bullet::addSprite()
{
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_bullet"]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    sprite->setRotation(angle);
}

void Bullet::launch()
{
    body->SetLinearVelocity(velocity);
}



void Bullet::initPhysics(b2World *world)
{
    body = world->CreateBody(createBody(getPosition()));
    body->CreateFixture(createFixture(createRectangularShape(_contentSize)));
    
    body->SetType(b2_kinematicBody);

    body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(180.0f - angle));
    

}
