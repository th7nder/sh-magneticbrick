//
//  SHSliderBox.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#include "SHSliderBox.hpp"

using namespace cocos2d;

SHSliderBox::SHSliderBox() : leftButton(nullptr), minus(nullptr), slider(nullptr), plus(nullptr), previousPercent(0), sliderCallback(nullptr)
{
    
}

SHSliderBox* SHSliderBox::create(GameHandler* handler, const std::string& leftImage, const float width)
{
    SHSliderBox * ret = new (std::nothrow) SHSliderBox();
    if (ret && ret->init(handler, leftImage, width))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool SHSliderBox::init(GameHandler* handler, const std::string &leftImage, const float width)
{
    if(!super::init()) return false;
    setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    gameHandler = handler;
    
    leftButton = cocos2d::ui::Button::create(leftImage);
    auto size = leftButton->getContentSize();
    setContentSize(cocos2d::Size(width, size.height));
    
    leftButton->setPosition(cocos2d::Vec2(size.width / 2, size.height / 2));
    addChild(leftButton);
    

    
    minus = SHButton::create(gameHandler, Globals::resources["icon_minus_white"]);
    minus->setPosition(cocos2d::Vec2(leftButton->getPositionX() + size.width, leftButton->getPositionY()));
    addChild(minus);    
    
    slider = SHSlider::create(Globals::resources["icon_line_white"], Globals::resources["icon_dot_white"]);
    slider->setPosition(cocos2d::Vec2(minus->getPositionX() + size.width / 2 + slider->getContentSize().width / 2, leftButton->getPositionY()));
    addChild(slider);
    
    plus =  SHButton::create(gameHandler, Globals::resources["icon_plus_white"]);
    plus->setPosition(cocos2d::Vec2(slider->getPositionX() + slider->getContentSize().width / 2 + size.width / 2, leftButton->getPositionY()));
    addChild(plus);
    
    
    setCallbacks();
    return true;
}

void SHSliderBox::setColor(const cocos2d::Color3B &color)
{
    super::setColor(color);
    leftButton->setColor(color);
    minus->setColor(color);
    slider->setColor(color);
    plus->setColor(color);
}


void SHSliderBox::setSliderCallback(const SHSlider::ccSliderCallback &callback)
{
    slider->addEventListener(callback);
    sliderCallback = callback;
}

void SHSliderBox::setCallbacks()
{
    minus->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(type == cocos2d::ui::Widget::TouchEventType::BEGAN)
        {
            int percent = slider->getPercent();
            if(percent - 1 >= 0)
            {
                slider->setPercent(percent - 1);
            } else
            {
                slider->setPercent(0);
            }
            
            
        
            if(sliderCallback) sliderCallback((Ref*)slider, SHSlider::EventType::ON_PERCENTAGE_CHANGED);
        }
    });
    
    
    plus->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(type == cocos2d::ui::Widget::TouchEventType::BEGAN)
        {
            int percent = slider->getPercent();
            if(percent + 1 <= 100)
            {
                slider->setPercent(percent + 1);
            } else
            {
                slider->setPercent(100);
            }
        
            if(sliderCallback) sliderCallback((Ref*)slider, SHSlider::EventType::ON_PERCENTAGE_CHANGED);
        }
    });
    
    
    leftButton->addTouchEventListener([this](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        if(type == cocos2d::ui::Widget::TouchEventType::BEGAN)
        {
            int percent = slider->getPercent();
            if(percent)
            {
                previousPercent = percent;
                slider->setPercent(0);
            } else
            {
                slider->setPercent(previousPercent);
            }
            
            if(sliderCallback) sliderCallback((Ref*)slider, SHSlider::EventType::ON_PERCENTAGE_CHANGED);
        }

    });
}

void SHSliderBox::setPercent(int percent)
{
    slider->setPercent(percent);
}


void SHSliderBox::setPreviousPercent(int percent)
{
    previousPercent = percent;
}
