//
//  JEDouble.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 21/06/2017.
//
//

#include "JEDouble.hpp"

JEDouble::JEDouble()
{
    
}

JEDouble::~JEDouble()
{
    
}

JEDouble* JEDouble::create(GameHandler* handler)
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



bool JEDouble::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void JEDouble::addSprite()
{
    auto str = "themes/jungle/extras/double_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);

}
