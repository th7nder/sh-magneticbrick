//
//  SESnowflakeSmall.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/06/2017.
//
//

#include "SESnowflakeSmall.hpp"


SESnowflakeSmall::SESnowflakeSmall()
{
    
}

SESnowflakeSmall::~SESnowflakeSmall()
{
    
}

SESnowflakeSmall* SESnowflakeSmall::create(GameHandler* handler)
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



bool SESnowflakeSmall::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    
    return true;

}


void SESnowflakeSmall::addSprite()
{
    auto str = "themes/snowland/extras/snowflake_small.png";
    sprite = cocos2d::Sprite::create(str);
    // sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPositionX(sprite->getPositionX() + sprite->getContentSize().width / 2);
    sprite->setPositionY(sprite->getPositionY() + sprite->getContentSize().height / 2);
    addChild(sprite);
}

