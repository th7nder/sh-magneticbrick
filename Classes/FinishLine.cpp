//
//  FinishLine.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/03/2017.
//
//

#include "FinishLine.hpp"

USING_NS_CC;
FinishLine::FinishLine()
{
    
}

FinishLine::~FinishLine()
{
    
}


// do wyjebania tak btw :)
// to do finishLineGameHandler, win
void FinishLine::addSprite()
{
    //gameHandler->setFinishLineY(getPositionY() + getContentSize().height);
    sprite = cocos2d::Sprite::create(Globals::resources["obstacle_finishline"]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
}

bool FinishLine::OnContactBegin(LevelObject *other, b2Body* otherBody)
{

    return false;
}

void FinishLine::initPhysics(b2World *world)
{
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
