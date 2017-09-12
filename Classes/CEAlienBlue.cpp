//
//  CEAlienBlue.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#include "CEAlienBlue.hpp"



CEAlienBlue::CEAlienBlue()
{
    
}

CEAlienBlue::~CEAlienBlue()
{
    
}

CEAlienBlue* CEAlienBlue::create(GameHandler* handler)
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



bool CEAlienBlue::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CEAlienBlue::addSprite()
{
    auto str = "themes/cosmic/extras/alien_blue_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    
}
