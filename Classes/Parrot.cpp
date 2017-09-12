//
//  Parrot.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 11/07/2017.
//
//

#include "Parrot.hpp"


#include "Parrot.hpp"



Parrot::Parrot()
{
    
}

Parrot::~Parrot()
{
    
}

Parrot* Parrot::create(GameHandler* handler)
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



bool Parrot::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    
    return true;
    
}


void Parrot::addSprite()
{
    auto str = "themes/jungle/extras/maverick.png";
    sprite = cocos2d::Sprite::create(str);
    // sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    addChild(sprite);
    
    if(orientation == "left")
    {
        sprite->setRotation(180);
        sprite->setFlippedY(true);
    }
}
