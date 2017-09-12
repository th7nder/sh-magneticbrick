//
//  CSEBarrier.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "CSEBarrier.hpp"

CSEBarrier::CSEBarrier()
{
    
}

CSEBarrier::~CSEBarrier()
{
    
}

CSEBarrier* CSEBarrier::create(GameHandler* handler)
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



bool CSEBarrier::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CSEBarrier::addSprite()
{
    auto str = "themes/construction/extras/barrier_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);

}
