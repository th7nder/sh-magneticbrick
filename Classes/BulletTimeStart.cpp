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


bool BulletTimeStart::OnContactBegin(LevelObject *other, b2Body* otherBody)
{

// to do bulletTimeStart
    return false;
}



void BulletTimeStart::initPhysics(b2World *world)
{
    
    //infinite runner refactor
    setPositionY(getPositionY() - 200);
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


