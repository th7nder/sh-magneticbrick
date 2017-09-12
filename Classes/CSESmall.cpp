//
//  CSESmall.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "CSESmall.hpp"


CSESmall::CSESmall()
{
    
}

CSESmall::~CSESmall()
{
    
}

CSESmall* CSESmall::create(GameHandler* handler)
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



bool CSESmall::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CSESmall::addSprite()
{
    auto str = "themes/construction/extras/small_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);

}



