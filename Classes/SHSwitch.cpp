//
//  SHSwitch.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#include "SHSwitch.hpp"



SHSwitch* SHSwitch::create(const std::string &onImage, const std::string &offImage, bool state)
{
    SHSwitch * ret = new (std::nothrow) SHSwitch();
    if (ret && ret->init(onImage, offImage, state))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool SHSwitch::init(const std::string &onImage, const std::string &offImage, bool state)
{
    if(!super::init(state ? onImage : offImage)) return false;
    this->onImage = onImage;
    this->offImage = offImage;
    this->isOn = state;
    

    
    addClickEventListener(CC_CALLBACK_1(SHSwitch::onClick, this));
    return true;
}

void SHSwitch::update(const std::string &on, const std::string &off)
{
    this->onImage = on;
    this->offImage = off;
    setState(isOn);
}

void SHSwitch::onClick(cocos2d::Ref *ref)
{
        setState(!isOn);
        switchCallback(ref);
}

void SHSwitch::setState(bool state)
{

    if(state)
    {
        loadTextureNormal(onImage);
        isOn = true;
    }
    else
    {
        loadTextureNormal(offImage);
        isOn = false;
    }
}


void SHSwitch::addSwitchListener(const ccWidgetClickCallback &callback)
{
    switchCallback = callback;
}
