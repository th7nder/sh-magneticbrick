//
//  BlackoutStop.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#include "BlackoutStop.hpp"


BlackoutStop::BlackoutStop()
{
    
}

BlackoutStop::~BlackoutStop()
{
    
}


bool BlackoutStop::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    // fix me
    //gameHandler->setBlackout(false);
    return false;
}


void BlackoutStop::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


