//
//  LevelFollower.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 28/06/2017.
//
//

#include "LevelFollower.hpp"

USING_NS_CC;
LevelFollower::LevelFollower() :
speed(0.0)
{
    
}

LevelFollower::~LevelFollower()
{

}


void LevelFollower::setProperties(cocos2d::ValueMap& props)
{
    super::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "LevelFollower -> initialSpeed isNull");
    speed = -(props["initialSpeed"].asFloat());
    
    previousPosition = Vec2::ZERO;
}


void LevelFollower::initPhysics(b2World* world)
{
    body = createDestroyer(world, Vec2::ZERO);
}

void LevelFollower::launch()
{
    body->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
}



void LevelFollower::interpolate(float alpha)
{
    Vec2 target(lerp(previousPosition.x, metersToPixels(body->GetPosition().x), alpha),
                lerp(previousPosition.y, metersToPixels(body->GetPosition().y), alpha));
    
    _parent->setPosition(target);
}

