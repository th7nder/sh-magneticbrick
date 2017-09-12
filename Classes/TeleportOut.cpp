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

TeleportOut* TeleportOut::create(GameHandler* handler)
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


bool TeleportOut::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    
    return true;
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
    auto size = getContentSize();
    body = world->CreateBody(createBody(getPositionX(), getPositionY() + size.height / 2));
    auto fixture = createFixture(createRectangularShape(size.width, size.height));
    fixture->filter.categoryBits = kFilterCategoryNonSolidObject;
    fixture->filter.maskBits = kFilterCategoryPlayer;
    fixture->isSensor = true;
    body->CreateFixture(fixture);
}
