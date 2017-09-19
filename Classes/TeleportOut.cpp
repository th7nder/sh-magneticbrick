//
//  TeleportOut.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/03/2017.
//
//

#include "TeleportOut.hpp"
USING_NS_CC;
TeleportOut::TeleportOut() : textureSize(0)
{
    
}

TeleportOut::~TeleportOut()
{
    
}



void TeleportOut::addSprite()
{
    auto number = StringUtils::format("%d", textureSize);
    sprite = Sprite::create(Globals::resources["obstacle_teleport_out_" + number]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
}


void TeleportOut::setProperties(ValueMap &properties)
{
    super::setProperties(properties);
    auto scale = Director::getInstance()->getContentScaleFactor();
    textureSize = (properties["width"].asFloat() * scale / 54.0);
    if(!properties["name"].isNull())
    {
        setName(properties["name"].asString());
    }
}


void TeleportOut::initPhysics(b2World *world)
{
    body = world->CreateBody(createBody(Vec2(getPositionX(), getPositionY() + _contentSize.height / 2)));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    fixture->isSensor = true;
    body->CreateFixture(fixture);
}
