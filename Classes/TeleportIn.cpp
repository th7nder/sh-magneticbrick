//
//  TeleportIn.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/03/2017.
//
//

#include "TeleportIn.hpp"
USING_NS_CC;
TeleportIn::TeleportIn() : textureSize(0), velocity(0.0)
{
    target = "";
}

TeleportIn::~TeleportIn()
{
    
}


void TeleportIn::addSprite()
{
    auto number = StringUtils::format("%d", textureSize);
    sprite = Sprite::create(Globals::resources["obstacle_teleport_in_" + number]);
    sprite->setAnchorPoint(Vec2::ZERO);
    addChild(sprite);
}


void TeleportIn::setProperties(ValueMap &properties)
{
    super::setProperties(properties);
    auto scale = Director::getInstance()->getContentScaleFactor();
    textureSize = (properties["width"].asFloat() * scale / 54.0);
    if(!properties["target"].isNull())
    {
        target = properties["target"].asString();
    }
    CCASSERT(!properties["velocity"].isNull(), "Velocity of teleport not set!");
    velocity = properties["velocity"].asFloat();
}




void TeleportIn::initPhysics(b2World *world)
{
    body = world->CreateBody(createBody(getPosition()));
    auto fixture = createFixture(createRectangularShape(_contentSize));
    fixture->isSensor = true;
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    body->CreateFixture(fixture);
}
