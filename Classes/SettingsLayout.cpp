//
//  SettingsLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#include "SettingsLayout.hpp"
USING_NS_CC;
SettingsLayout::SettingsLayout() : backTarget(nullptr)
{
    
}

SettingsLayout::~SettingsLayout()
{
    _eventDispatcher->removeEventListener(keyboardListener);
}

void SettingsLayout::setBackTarget(cocos2d::ui::Layout *back)
{
    backTarget = back;
}

SettingsLayout* SettingsLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    SettingsLayout * ret = new (std::nothrow) SettingsLayout();
    if (ret && ret->initWithSize(size, handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool SettingsLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    this->gameHandler = handler;
    setContentSize(size);

    createMusicSliderBox();
    createSfxSliderBox();
    createBackButton();
    createForceBox();
    

    addChild(createCopyright(Vec2(320, 50), 20.0));
    addChild(createSettingsLabel(Vec2(340, Globals::getSmallPhone() ? 1056 - 30 : 1056), 51.0));
    
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            if(this->getPositionY() == 0 && this->isEnabled() && this->isVisible() && this->getOpacity() >= 255)
            {
                this->gameHandler->onBackButtonClicked();
            }
            
        }
    };
    
   _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    

    return true;
}

void SettingsLayout::setColor(const Color3B& color)
{
    for(const auto& child : getChildren())
    {
        child->setColor(color);
    }
}




cocos2d::Label* SettingsLayout::createCopyright(cocos2d::Vec2 pos, float fontSize)
{
    cocos2d::Label* copyright;
    copyright = Label::createWithTTF("© 2017 Skyhorn. All Rights Reserved.", Globals::gameFont, fontSize);
    copyright->setPosition(pos);
    
    return copyright;
}

cocos2d::Label* SettingsLayout::createSettingsLabel(cocos2d::Vec2 pos, float fontSize)
{
    cocos2d::Label* settings;
    settings = Label::createWithTTF("SETTINGS", Globals::gameFont, fontSize);
    settings->setPosition(pos);
    
    return settings;
}


void SettingsLayout::createMusicSliderBox()
{
    auto size = getContentSize();
    auto msb = SHSliderBox::create(gameHandler, Globals::resources["icon_music_white"], size.width * 0.86);
    msb->setPosition(cocos2d::Vec2(size.width / 2, size.height / 2 + msb->getContentSize().height * 2.0));
    msb->setPercent(gameHandler->getMusicVolume());
    msb->setPreviousPercent(gameHandler->getPreviousMusicVolume());
    addChild(msb);
    
    
    msb->setSliderCallback([this](Ref* sender, SHSlider::EventType type){
        if(type == SHSlider::EventType::ON_PERCENTAGE_CHANGED)
        {
            SHSlider* sld = dynamic_cast<SHSlider*>(sender);
            gameHandler->setPreviousMusicVolume(gameHandler->getMusicVolume());
            gameHandler->setMusicVolume(sld->getPercent());
        }
    });
    
}

void SettingsLayout::createSfxSliderBox()
{
    auto size = getContentSize();
    auto ssb = SHSliderBox::create(gameHandler, Globals::resources["icon_sfx_white"], size.width * 0.86);
    ssb->setPosition(cocos2d::Vec2(size.width / 2, size.height / 2 + (ssb->getContentSize().height * 0.5)));
    ssb->setPercent(gameHandler->getSfxVolume());
    ssb->setPreviousPercent(gameHandler->getPreviousSfxVolume());
    addChild(ssb);
    
    ssb->setSliderCallback([this](Ref* sender, SHSlider::EventType type){
        if(type == SHSlider::EventType::ON_PERCENTAGE_CHANGED)
        {
            SHSlider* sld = dynamic_cast<SHSlider*>(sender);
            gameHandler->setPreviousSfxVolume(gameHandler->getSfxVolume());
            gameHandler->setSfxVolume(sld->getPercent());
        }
    });
}

void SettingsLayout::createBackButton()
{
    auto size = getContentSize();
    const Vec2 pos(58, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    
    auto backButton = SHButton::create(gameHandler, Globals::resources["icon_back_left_white"]);
    backButton->setPosition(pos);
    backButton->addClickEventListener(CC_CALLBACK_1(SettingsLayout::onBackButtonClicked, this));
    addChild(backButton);

}


void SettingsLayout::createForceBox()
{
    auto size = getContentSize();
    auto forceBox = SHSwitchBox::create(gameHandler, Globals::resources["icon_forcetouch_white"], size.width * 0.86);
    forceBox->setPosition(cocos2d::Vec2(size.width / 2, 459));
    if(gameHandler->getForceTouchAvailable())
    {
        forceBox->setState(gameHandler->getForceTouch());
        forceBox->setEnabled(true);
    }
    else
    {
        forceBox->setState(false);
        forceBox->setEnabled(false);
        
    }
    addChild(forceBox);
    
    forceBox->addSwitchListener([this](Ref* sender){
        SHSwitch* shSwitch = dynamic_cast<SHSwitch*>(sender);
        gameHandler->setForceTouch(shSwitch->getState());
    });
}


void SettingsLayout::onBackButtonClicked(cocos2d::Ref *ref)
{
    gameHandler->onBackButtonClicked();
}


void SettingsLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{

    if(isEnabled())
    {
        if(touch->getDelta().x > 50)
        {
            gameHandler->onBackButtonClicked();
        }  
    }

}
