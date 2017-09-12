//
//  Walls.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 26/05/2017.
//
//

#include "Walls.hpp"
USING_NS_CC;

Walls::Walls() :
rightBody(nullptr),
speed(0.0)
{
    
}

Walls::~Walls()
{
    rightBody->GetWorld()->DestroyBody(rightBody);
}


Walls* Walls::create(GameHandler* handler)
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

bool Walls::init(GameHandler* handler)
{
    if(!super::init(gameHandler)) return false;
    gameHandler = handler;
    
    return true;
}

void Walls::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "initialSpeed was not set in map!");
    speed = (props["initialSpeed"].asFloat());
}

b2Body* Walls::createDestroyer(b2World* world, float x, float y)
{
    auto bodyDef = createBody(x, y);
    bodyDef->type = b2_kinematicBody;
    
    auto ret = world->CreateBody(bodyDef);
    auto shape = new b2EdgeShape;
    shape->Set(b2Vec2(0, -1), b2Vec2(0, 1));
    auto fixture = super::createFixture(shape);
    fixture->filter.categoryBits = kFilterCategorySolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    ret->CreateFixture(fixture);
    ret->SetLinearVelocity(b2Vec2(0, pixelsToMeters(speed)));
    ret->SetBullet(true);
    ret->SetType(b2_kinematicBody);
    return ret;
}

void Walls::initPhysics(b2World* world)
{
    body = createDestroyer(world, 0, getPositionY());
    rightBody = createDestroyer(world, ownVisibleSize.width, getPositionY());
}
