//
//  CEAlienGreen.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#include "CEAlienGreen.hpp"



CEAlienGreen::CEAlienGreen()
{
    
}

CEAlienGreen::~CEAlienGreen()
{
    
}

CEAlienGreen* CEAlienGreen::create(GameHandler* handler)
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



bool CEAlienGreen::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CEAlienGreen::addSprite()
{
    auto str = "themes/cosmic/extras/alien_green_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    
}
