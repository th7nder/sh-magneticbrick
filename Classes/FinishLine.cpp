//
//  FinishLine.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/03/2017.
//
//

#include "FinishLine.hpp"


FinishLine::FinishLine()
{
    
}

FinishLine::~FinishLine()
{
    
}

FinishLine* FinishLine::create(GameHandler* handler)
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


bool FinishLine::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void FinishLine::addSprite()
{
    gameHandler->setFinishLineY(getPositionY() + getContentSize().height);
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_finishline"]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
}

bool FinishLine::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    gameHandler->onPlayerWin();

    return false;
}

void FinishLine::initPhysics(b2World *world)
{
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY()));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
