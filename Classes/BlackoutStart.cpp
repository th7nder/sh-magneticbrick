//
//  BlackoutStart.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#include "BlackoutStart.hpp"


BlackoutStart::BlackoutStart()
{
    
}

BlackoutStart::~BlackoutStart()
{
    
}


bool BlackoutStart::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    // fix me
    //gameHandler->setBlackout(true);
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_blackout"].c_str());
    return false;
}



void BlackoutStart::initPhysics(b2World *world)
{
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


