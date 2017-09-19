//
//  Star.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 09/03/2017.
//
//

#include "Star.hpp"

USING_NS_CC;
Star::Star() : number(0)
{
  
}

Star::~Star()
{
    
}

// to do removing stars, colors

void Star::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    CCASSERT(!props["name"].isNull(), "initialSpeed was not set in map!");
    number = props["name"].asInt();
    
    
    //if(gameHandler->getStar(number)) remove = true;
}


void Star::addSprite()
{
    if(remove) return;
    sprite = cocos2d::Sprite::create(Globals::resources["icon_star_collect_white"]);
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setCascadeOpacityEnabled(true);
    auto seq = Sequence::create(FadeTo::create(0.5, 10), FadeIn::create(0.3), DelayTime::create(0.4), NULL);
    sprite->runAction(RepeatForever::create(seq));
    addChild(sprite);
}

bool Star::OnContactBegin(LevelObject *other, b2Body* otherBody)
{
    return false;
}

void Star::initPhysics(b2World *world)
{
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
