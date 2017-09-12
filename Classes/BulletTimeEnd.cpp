//
//  BulletTimeEnd.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#include "BulletTimeEnd.hpp"


BulletTimeEnd::BulletTimeEnd()
{
    
}

BulletTimeEnd::~BulletTimeEnd()
{
    
}

BulletTimeEnd* BulletTimeEnd::create(GameHandler* handler)
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


bool BulletTimeEnd::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool BulletTimeEnd::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    return false;
}


void BulletTimeEnd::launch()
{
    gameHandler->setBulletTime(false);
}


void BulletTimeEnd::initPhysics(b2World *world)
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
