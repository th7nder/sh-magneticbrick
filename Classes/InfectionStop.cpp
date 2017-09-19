//
//  InfectionStop.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#include "InfectionStop.hpp"



InfectionStop::InfectionStop()
{
    
}

InfectionStop::~InfectionStop()
{
    
}


bool InfectionStop::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    return false;
}

/*void InfectionStop::launch()
{
    // fix me
   // gameHandler->setInfection(false);
}*/



void InfectionStop::initPhysics(b2World *world)
{
    setPositionY(getPositionY() + 200.0);
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


