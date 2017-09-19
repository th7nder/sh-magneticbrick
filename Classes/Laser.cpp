//
//  Laser.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#include "Laser.hpp"

USING_NS_CC;


std::string Laser::leftTexture = "";
std::string Laser::centerTexture = "";
std::string Laser::rightTexture = "";

Laser::Laser()
{
    
}

Laser::~Laser()
{
    
}


void Laser::setProperties(ValueMap &properties)
{
    super::setProperties(properties);
    CCASSERT(!properties["name"].isNull(), "Laser -> name.isNull");
    auto name = properties["name"].asString();
    setName(name);
}

void Laser::addSprite()
{

    auto spr = Sprite::create(leftTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    const float sprY = 16;
    spr->setPositionY(sprY);
    addChild(spr);
    
    
    auto width = spr->getContentSize().width;
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().width / width;
    int amount = getContentSize().width / width;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 2)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(width, sprY));
        spr->setContentSize(Size((amount - 2) * width, height));
        addChild(spr);
    }
    
    spr = Sprite::create(rightTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPositionX(width + ((amount - 2) * width));
    spr->setPositionY(sprY);
    addChild(spr);
}

bool Laser::OnContactBegin(LevelObject *other, b2Body *body)
{
    return true;
}



