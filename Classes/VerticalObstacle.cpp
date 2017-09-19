//
//  VerticalObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/03/2017.
//
//

#include "VerticalObstacle.hpp"

USING_NS_CC;

std::string VerticalObstacle::upTexture = "";
std::string VerticalObstacle::centerTexture = "";
std::string VerticalObstacle::downTexture = "";
VerticalObstacle::VerticalObstacle()
{
    angle = 0.0;
}

VerticalObstacle::~VerticalObstacle()
{
    
}

void VerticalObstacle::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
}


void VerticalObstacle::addSprite()
{
    setRotation(angle);
    auto spr = Sprite::create(downTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    addChild(spr);
    
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().height / height;
    int amount = getContentSize().height / height;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 2)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(0, height));
        spr->setContentSize(Size(spr->getContentSize().width, (amount - 2) * height));
        addChild(spr);
    }
    
    spr = Sprite::create(upTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPosition(Vec2(0, height + ((amount - 2) * height)));
    addChild(spr);
}
