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

InfectionStop* InfectionStop::create(GameHandler* handler)
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


bool InfectionStop::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool InfectionStop::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    return false;
}

void InfectionStop::launch()
{
    gameHandler->setInfection(false);
}



void InfectionStop::initPhysics(b2World *world)
{
    setPositionY(getPositionY() + 200.0);
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


