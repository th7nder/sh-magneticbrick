//
//  CEAlienRed.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#include "CEAlienRed.hpp"

CEAlienRed::CEAlienRed()
{
    
}

CEAlienRed::~CEAlienRed()
{
    
}

CEAlienRed* CEAlienRed::create(GameHandler* handler)
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



bool CEAlienRed::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CEAlienRed::addSprite()
{
    auto str = "themes/cosmic/extras/alien_red_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    
}
