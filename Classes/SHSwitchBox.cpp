
//
//  SHSwitchBox.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#include "SHSwitchBox.hpp"
SHSwitchBox* SHSwitchBox::create(GameHandler* gameHandler, const std::string& leftImage, const float width)
{
    SHSwitchBox * ret = new (std::nothrow) SHSwitchBox();
    if (ret && ret->init(gameHandler, leftImage, width))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool SHSwitchBox::init(GameHandler* handler, const std::string &leftImage, const float width)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    
    leftButton = cocos2d::ui::Button::create(leftImage);
    leftButton->setEnabled(false);
    auto size = leftButton->getContentSize();
    setContentSize(cocos2d::Size(width, size.height));
    
    leftButton->setPosition(cocos2d::Vec2(size.width / 2, size.height / 2));
    addChild(leftButton);
    
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    shSwitch = SHSwitch::create(Globals::resources["icon_on_" + strColor], Globals::resources["icon_off_" + strColor], true);
    float targetX = leftButton->getPositionX() + size.width + (width - (leftButton->getPositionX() + size.width)) / 2;
    shSwitch->setPosition(cocos2d::Vec2(targetX, size.height / 2));
    addChild(shSwitch);
    return true;
}


void SHSwitchBox::update(const std::string &leftImage)
{
    leftButton->loadTextureNormal(leftImage);
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    shSwitch->update(Globals::resources["icon_on_" + strColor], Globals::resources["icon_off_" + strColor]);
}

void SHSwitchBox::addSwitchListener(const SHSwitch::ccWidgetClickCallback &callback)
{
    shSwitch->addSwitchListener(callback);
}

void SHSwitchBox::setState(bool state)
{
    shSwitch->setState(state);
}

void SHSwitchBox::setEnabled(bool state)
{
    shSwitch->setEnabled(state);
}
