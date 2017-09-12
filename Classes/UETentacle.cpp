//
//  UETentacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "UETentacle.hpp"


UETentacle::UETentacle()
{
    
}

UETentacle::~UETentacle()
{
    
}

UETentacle* UETentacle::create(GameHandler* handler)
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



bool UETentacle::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    return true;
}


void UETentacle::addSprite()
{
    auto str = "themes/underwater/extras/tentacle_" + orientation + ".png";
    sprite = cocos2d::Sprite::create(str);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
    
}
