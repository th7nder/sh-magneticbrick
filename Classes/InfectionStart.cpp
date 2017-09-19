//
//  InfectionStart.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "InfectionStart.hpp"



InfectionStart::InfectionStart()
{
    
}

InfectionStart::~InfectionStart()
{
    
}



bool InfectionStart::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    //fix me
    //gameHandler->setInfection(true);
    return false;
}



void InfectionStart::initPhysics(b2World *world)
{
    setPositionY(getPositionY() - 200);
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


