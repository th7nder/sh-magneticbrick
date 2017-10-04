//
//  BaseLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/09/2017.
//
//

#include "ui/UILayout.h"
#include "cocos2d.h"
#include "BaseLayout.hpp"

USING_NS_CC;

bool BaseLayout::init()
{
    if(!super::init()) return false;
    
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            if(isTopView())
            {
                actionBackButton();
            }
            
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    return true;
}

void BaseLayout::setColor(const Color3B& color)
{
    super::setColor(color);
    for(const auto& child : getChildren())
    {
        const auto childColor = child->getColor();
        if(childColor == cocos2d::Color3B::BLACK || childColor == cocos2d::Color3B::WHITE)
        {
            child->setColor(color);
        }
    }
}

bool BaseLayout::isTopView()
{
    return (getPositionY() == 0 && isEnabled() && isVisible() && getOpacity() == 255);
}


