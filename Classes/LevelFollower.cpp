//
//  LevelFollower.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 28/06/2017.
//
//

#include "LevelFollower.hpp"

LevelFollower::LevelFollower() :
rightBody(nullptr),
speed(0.0)
{
    
}

LevelFollower::~LevelFollower()
{

}


LevelFollower* LevelFollower::create(GameHandler* handler)
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

bool LevelFollower::init(GameHandler* handler)
{
    if(!super::init(gameHandler)) return false;
    gameHandler = handler;
    

    
    return true;
}

void LevelFollower::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "initialSpeed was not set in map!");
    speed = -(props["initialSpeed"].asFloat());
    
    previousPosition = Vec2::ZERO;
}

b2Body* LevelFollower::createDestroyer(b2World* world, float x, float y)
{
    auto bodyDef = createBody(x, y);
    bodyDef->type = b2_kinematicBody;
    
    auto ret = world->CreateBody(bodyDef);
    auto shape = new b2EdgeShape;
    shape->Set(b2Vec2(0, -1), b2Vec2(0, 1));
    auto fixture = super::createFixture(shape);
    fixture->filter.categoryBits = 0;
    fixture->filter.maskBits = 0;
    ret->CreateFixture(fixture);
    ret->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    ret->SetBullet(true);
    ret->SetType(b2_kinematicBody);
    return ret;
}

void LevelFollower::savePreviousStates()
{
    previousPosition = Vec2(body->GetPosition().x, body->GetPosition().y);
}

void LevelFollower::interpolate(float alpha)
{
    Vec2 target(metersToPixels(lerp(previousPosition.x, body->GetPosition().x, alpha)), metersToPixels(lerp(previousPosition.y, body->GetPosition().y, alpha)));
    
    _parent->setPosition(target);
}

void LevelFollower::initPhysics(b2World* world)
{
    body = createDestroyer(world, 0, 0);
}


