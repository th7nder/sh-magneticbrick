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



bool BulletTimeEnd::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    return false;
}


/*void BulletTimeEnd::launch()
{
    // fix me bulletTimeTrigger
    //gameHandler->setBulletTime(false);
}*/


void BulletTimeEnd::initPhysics(b2World *world)
{
    setPositionY(getPositionY() + 200.0);
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
