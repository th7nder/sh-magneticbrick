//
//  Laser.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#include "Laser.hpp"


Laser::Laser()
{
    
}

Laser::~Laser()
{
    
}

Laser* Laser::create(GameHandler* handler)
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


bool Laser::init(GameHandler* handler)
{
    if(!LevelObject::init(handler)) return false;
    gameHandler = handler;
    const std::string lastThemeCodename = "obstacle_laser";
    leftTexture = Globals::resources[lastThemeCodename + "_left"];
    centerTexture = Globals::resources[lastThemeCodename + "_center"];
    rightTexture = Globals::resources[lastThemeCodename + "_right"];
    return true;
}


void Laser::addSprite()
{


    
    auto spr = Sprite::create(leftTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    const float sprY = 16;
    spr->setPositionY(sprY);
    addChild(spr);
    
    
    auto width = spr->getContentSize().width;
    auto height = spr->getContentSize().height;
    float fAmount = getContentSize().width / width;
    int amount = getContentSize().width / width;
    if(fAmount - amount > 0.5)
    {
        amount++;
    }
    
    float centerWidth = (amount - 2) * width;
    float maxWidth = width + centerWidth + width;
    if(maxWidth < this->width)
    {
        centerWidth += this->width - maxWidth;
    }
    if(amount > 2)
    {
        spr = Sprite::create(centerTexture);
        spr->setAnchorPoint(Vec2::ZERO);
        spr->setPosition(Vec2(width, sprY));
        spr->setContentSize(Size(centerWidth, height));
        addChild(spr);
    }
    
    spr = Sprite::create(rightTexture);
    spr->setAnchorPoint(Vec2::ZERO);
    spr->setPositionX(centerWidth + width);
    spr->setPositionY(sprY);
    addChild(spr);
    
    
}


void Laser::setProperties(ValueMap &properties)
{
    HorizontalObstacle::setProperties(properties);
    CCASSERT(!properties["name"].isNull(), "Laser without a name!");
    auto name = properties["name"].asString();
    setName(name);
}
