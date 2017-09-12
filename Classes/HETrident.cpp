//
//  HETrident.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "HETrident.hpp"


HETrident::HETrident()
{
    
}

HETrident::~HETrident()
{
    
}

HETrident* HETrident::create(GameHandler* handler)
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



bool HETrident::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void HETrident::addSprite()
{
    auto str = "themes/hell/extras/trident_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    
}
