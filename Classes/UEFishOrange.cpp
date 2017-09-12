//
//  UEFishOrange.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "UEFishOrange.hpp"


UEFishOrange::UEFishOrange()
{
    
}

UEFishOrange::~UEFishOrange()
{
    
}

UEFishOrange* UEFishOrange::create(GameHandler* handler)
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



bool UEFishOrange::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    
    return true;
    
}


void UEFishOrange::addSprite()
{
    auto str = "themes/underwater/extras/fish_orange.png";
    sprite = cocos2d::Sprite::create(str);
    // sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    addChild(sprite);
    
    if(orientation == "left")
    {
        sprite->setRotation(180);
        sprite->setFlippedY(true);
    }
}
