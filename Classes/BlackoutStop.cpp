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

BlackoutStop* BlackoutStop::create(GameHandler* handler)
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


bool BlackoutStop::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool BlackoutStop::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    
    gameHandler->setBlackout(false);
    return false;
}


void BlackoutStop::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


