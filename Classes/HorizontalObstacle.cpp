//
//  HorizontalObstacle.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 30/01/2017.
//
//



#include "HorizontalObstacle.hpp"



USING_NS_CC;

std::string HorizontalObstacle::leftTexture = "";
std::string HorizontalObstacle::centerTexture = "";
std::string HorizontalObstacle::rightTexture = "";

HorizontalObstacle::HorizontalObstacle()
{

}

HorizontalObstacle::~HorizontalObstacle()
{

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
    
}


// sth is reduntant here
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

bool HorizontalObstacle::OnContactBegin(LevelObject *other, b2Body *body)
{
    return true;
}
