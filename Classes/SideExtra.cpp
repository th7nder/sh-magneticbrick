//
//  SideExtra.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#include "SideExtra.hpp"

USING_NS_CC;

SideExtra::SideExtra(const std::string& texture) :
texture(texture),
orientation("")
{
    
}

SideExtra::~SideExtra()
{
    
}

int SideExtra::getZ() const
{
    return -1;
}
void SideExtra::setProperties(ValueMap &props)
{
    super::setProperties(props);
    orientation = props["orientation"].asString();
}

void SideExtra::addSprite()
{
    sprite = cocos2d::Sprite::create(texture);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
}
