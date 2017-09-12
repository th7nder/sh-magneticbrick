//
//  BulletTimeStart.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#include "BulletTimeStart.hpp"

BulletTimeStart::BulletTimeStart()
{
    
}

BulletTimeStart::~BulletTimeStart()
{
    
}

BulletTimeStart* BulletTimeStart::create(GameHandler* handler)
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


bool BulletTimeStart::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool BulletTimeStart::OnContactBegin(LevelObject *other, b2Body* otherBody)
{

    gameHandler->setBulletTime(true);
    return false;
}



void BulletTimeStart::initPhysics(b2World *world)
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


