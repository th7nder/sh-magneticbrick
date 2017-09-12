//
//  HorizontalObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//



#include "HorizontalObstacle.hpp"

HorizontalObstacle::HorizontalObstacle() : leftTexture(""), centerTexture(""), rightTexture(""), physics(true)
{
    
}

HorizontalObstacle::~HorizontalObstacle()
{

}

HorizontalObstacle* HorizontalObstacle::create(GameHandler* handler)
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


bool HorizontalObstacle::init(GameHandler* handler)
{
    if(!super::init(handler)) return false;
    gameHandler = handler;
    const auto lastThemeCodename = "obstacle_" +  handler->getLastTheme().getCodeName();
    leftTexture = Globals::resources[lastThemeCodename + "_left"];
    centerTexture = Globals::resources[lastThemeCodename + "_center"];
    rightTexture = Globals::resources[lastThemeCodename + "_right"];
    
    return true;
}

void HorizontalObstacle::initPhysics(b2World *world)
{
    if(physics)
    {
        super::initPhysics(world);
    }
}


void HorizontalObstacle::setProperties(ValueMap &props)
{
    LevelObject::setProperties(props);
    if(props["opened"].isNull())
    {
        opened = Closed;
    }
    else
    {
        opened = HorizontalState(props["opened"].asInt());
    }
    
    if(!props["physics"].isNull())
    {
        physics = props["physics"].asBool();
    } else {
        physics = true;
    }
}

void HorizontalObstacle::addSprite()
{
    Sprite* spr = nullptr;
    if(opened != LeftOpened && opened != BothOpened)
    {
       spr = Sprite::create(leftTexture);
    }
    else
    {
        spr = Sprite::create(centerTexture);
    }
    spr->setAnchorPoint(Vec2::ZERO);
    addChild(spr);
    
    auto width = spr->getContentSize().width;
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().width / width;
    int amount = getContentSize().width / width;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    if(amount > 2)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(width, 0));
        spr->setContentSize(Size((amount - 2) * width, height));
        addChild(spr);
    }
    
    
    if(opened != RightOpened && opened != BothOpened)
    {
        spr = Sprite::create(rightTexture);
    }
    else
    {
        spr = Sprite::create(centerTexture);
    }
    
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPositionX(width + ((amount - 2) * width));
    addChild(spr);
}
