//
//  Walls.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 26/05/2017.
//
//

#include "Walls.hpp"
USING_NS_CC;

Walls::Walls() :
rightBody(nullptr),
speed(0.0)
{
    
}

Walls::~Walls()
{
    rightBody->GetWorld()->DestroyBody(rightBody);
}


void Walls::setProperties(ValueMap &props)
{
    super::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "Walls -> initialSpeed isNull");
    speed = (props["initialSpeed"].asFloat());
}

void Walls::initPhysics(b2World* world)
{
    body = createDestroyer(world, Vec2(0, getPositionY()));
    rightBody = createDestroyer(world, Vec2(_director->getVisibleSize().width, getPositionY()));
}


bool Walls::OnContactBegin(LevelObject *other, b2Body *body)
{
    return true;
}

void Walls::interpolate(float alpha)
{
    
}

void Walls::savePreviousStates()
{
    
}

void Walls::launch()
{
    body->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    rightBody->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
}






