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


void Walls::setProperties(ValueMap &props)
{
    super::setProperties(props);
    CCASSERT(!props["initialSpeed"].isNull(), "LevelFollower -> initialSpeed isNull");
    speed = (props["initialSpeed"].asFloat());
}

bool Walls::OnContactBegin(LevelObject *other, b2Body *body)
{
    return true;
}

b2Body* Walls::getRightBody()
{
    return rightBody;
}


b2Body* Walls::createDestroyer(b2World* world, const cocos2d::Vec2& pos)
{
    auto bodyDef = createBody(pos);
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
    body = createDestroyer(world, Vec2(0, getPositionY()));
    rightBody = createDestroyer(world, Vec2(_director->getVisibleSize().width, getPositionY()));
}
