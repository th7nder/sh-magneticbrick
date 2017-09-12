//
//  CSEBall.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "CSEBall.hpp"

CSEBall::CSEBall()
{
    
}

CSEBall::~CSEBall()
{
    
}

CSEBall* CSEBall::create(GameHandler* handler)
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



bool CSEBall::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CSEBall::addSprite()
{
    auto str = "themes/construction/extras/ball_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    

}
