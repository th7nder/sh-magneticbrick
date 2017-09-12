//
//  CECometBlue.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#include "CECometBlue.hpp"

CECometBlue::CECometBlue()
{
    
}

CECometBlue::~CECometBlue()
{
    
}


CECometBlue* CECometBlue::create(GameHandler* handler)
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



bool CECometBlue::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CECometBlue::addSprite()
{
    auto str = "themes/cosmic/extras/comet_blue.png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    addChild(sprite);
}
