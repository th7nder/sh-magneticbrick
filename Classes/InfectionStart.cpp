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

InfectionStart* InfectionStart::create(GameHandler* handler)
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


bool InfectionStart::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool InfectionStart::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    gameHandler->setInfection(true);
    return false;
}



void InfectionStart::initPhysics(b2World *world)
{
    setPositionY(getPositionY() - 200);
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


