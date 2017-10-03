//
//  Destroyer.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 27/09/2017.
//

#include "Destroyer.hpp"

USING_NS_CC;

Destroyer::Destroyer() :
speed(0.0)
{
    CCLOG("creating destoyer");
}

Destroyer::~Destroyer()
{
    
}


void Destroyer::setProperties(ValueMap &props)
{
    super::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "Destroyer -> initialSpeed isNull");
    speed = (props["initialSpeed"].asFloat());
}

void Destroyer::initPhysics(b2World* world)
{
    Size size = _director->getVisibleSize();
    body = createDestroyer(world, Vec2(0, +_contentSize.height), b2Vec2(-pixelsToMeters(size.width / 2), 0), b2Vec2(pixelsToMeters(size.width / 2), 0));
    
    auto fixture = body->GetFixtureList();
    fixture->SetSensor(true);

    auto filter = body->GetFixtureList()->GetFilterData();
    filter.categoryBits = kFilterCategoryDestroyer;
    filter.maskBits = kFilterCategorySolidObject | kFilterCategoryLevel | kFilterCategoryNonSolidObject;
    body->GetFixtureList()->SetFilterData(filter);
}


bool Destroyer::OnContactBegin(LevelObject *other, b2Body *body)
{
    CCLOG("destroyer destroying: %s", other->getDescription().c_str());
    return false;
}

void Destroyer::interpolate(float alpha)
{
    
}

void Destroyer::savePreviousStates()
{
    
}

void Destroyer::launch()
{
    body->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
}






