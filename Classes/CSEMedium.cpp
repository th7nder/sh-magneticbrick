//
//  CSEMedium.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "CSEMedium.hpp"



CSEMedium::CSEMedium()
{
    
}

CSEMedium::~CSEMedium()
{
    
}

CSEMedium* CSEMedium::create(GameHandler* handler)
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



bool CSEMedium::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void CSEMedium::addSprite()
{
    auto str = "themes/construction/extras/medium_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);

}
