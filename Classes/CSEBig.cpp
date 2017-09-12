//
//  CSEBig.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "CSEBig.hpp"


CSEBig::CSEBig()
{
    
}

CSEBig::~CSEBig()
{
    
}

CSEBig* CSEBig::create(GameHandler* handler)
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



bool CSEBig::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CSEBig::addSprite()
{
    auto str = "themes/construction/extras/big_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    

}
