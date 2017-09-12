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

BlackoutStart* BlackoutStart::create(GameHandler* handler)
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


bool BlackoutStart::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


bool BlackoutStart::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    gameHandler->setBlackout(true);
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_blackout"].c_str());
    return false;
}



void BlackoutStart::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}


