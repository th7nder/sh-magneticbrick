//
//  WEHat.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#include "WEHat.hpp"

WEHat::WEHat()
{
    
}

WEHat::~WEHat()
{
    
}

WEHat* WEHat::create(GameHandler* handler)
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



bool WEHat::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void WEHat::addSprite()
{
    auto str = "themes/western/extras/hat.png";
    sprite = cocos2d::Sprite::create(str);
    // sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    addChild(sprite);
}
