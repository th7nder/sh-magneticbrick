//
//  VerticalObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/03/2017.
//
//

#include "VerticalObstacle.hpp"
VerticalObstacle::VerticalObstacle() : downTexture(""), centerTexture(""), upTexture("")
{
    angle = 0.0;
}

VerticalObstacle::~VerticalObstacle()
{
    
}

VerticalObstacle* VerticalObstacle::create(GameHandler* handler)
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


bool VerticalObstacle::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    const auto lastThemeCodename = "obstacle_" +  handler->getLastTheme().getCodeName();
    downTexture = Globals::resources[lastThemeCodename + "_vert_down"];
    centerTexture = Globals::resources[lastThemeCodename + "_vert_center"];
    upTexture = Globals::resources[lastThemeCodename + "_vert_up"];
    return true;
}


void VerticalObstacle::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
}

void VerticalObstacle::initPhysics(b2World *world)
{
    super::initPhysics(world);
    //body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(180.0 - angle));
}

void VerticalObstacle::addSprite()
{
    setRotation(angle);
    auto spr = Sprite::create(downTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    addChild(spr);
    
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().height / height;
    int amount = getContentSize().height / height;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 2)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(0, height));
        spr->setContentSize(Size(spr->getContentSize().width, (amount - 2) * height));
        addChild(spr);
    }
    
    spr = Sprite::create(upTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPosition(Vec2(0, height + ((amount - 2) * height)));
    addChild(spr);
}
