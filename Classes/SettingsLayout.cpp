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
    gameHandler = handler;
    setContentSize(size);
    createMusicSliderBox();
    createSfxSliderBox();
    createBackButton();
    createForceBox();
    
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
    
    copyright = createCopyright(Vec2(320, 50), 20.0);
    addChild(copyright);
    
    settingsLabel = createSettingsLabel(Vec2(340, Globals::getSmallPhone() ? 1056 - 30 : 1056), 51.0);
    addChild(settingsLabel);
    

    return true;
}



cocos2d::Label* SettingsLayout::createCopyright(cocos2d::Vec2 pos, float fontSize)
{
    cocos2d::Label* copyright;
    auto color = gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    copyright = Label::createWithTTF("© 2017 Skyhorn. All Rights Reserved.", Globals::gameFont, fontSize);
    copyright->setColor(color);
    copyright->setPosition(pos);
    
    return copyright;
}

cocos2d::Label* SettingsLayout::createSettingsLabel(cocos2d::Vec2 pos, float fontSize)
{
    cocos2d::Label* settings;
    settings = Label::createWithTTF("SETTINGS", Globals::gameFont, fontSize);
    settings->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    settings->setPosition(pos);
    
    return settings;
}


void SettingsLayout::createMusicSliderBox()
{
    auto size = getContentSize();
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    msb = SHSliderBox::create(gameHandler, Globals::resources["icon_music_" + strColor], size.width * 0.86);
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
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    ssb = SHSliderBox::create(gameHandler, Globals::resources["icon_sfx_" + strColor], size.width * 0.86);
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
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    
    const Vec2 pos(58, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    backButton = SHButton::create(gameHandler, Globals::resources["icon_back_left_" + strColor]);
    backButton->setPosition(pos);
    backButton->addClickEventListener(SettingsLayout::onBackButtonClicked);
    addChild(backButton);

}


void SettingsLayout::createForceBox()
{
    auto size = getContentSize();
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    forceBox = SHSwitchBox::create(gameHandler, Globals::resources["icon_forcetouch_" + strColor], size.width * 0.86);
    forceBox->setPosition(cocos2d::Vec2(size.width / 2, ssb->getPositionY() - (ssb->getContentSize().height * 1.5)));
    if(gameHandler->getForceTouchAvailable())
    {
        forceBox->setState(gameHandler->getForceTouch());
        forceBox->setEnabled(true);
    } else {
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
    auto button = dynamic_cast<SHButton*>(ref);
    if(button != nullptr)
    {
        auto settingsLayout = dynamic_cast<SettingsLayout*>(button->getParent());
        if(settingsLayout != nullptr)
        {
            settingsLayout->gameHandler->onBackButtonClicked();
        }
    }
}

void SettingsLayout::updateUI()
{
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    auto color = gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    backButton->loadTextureNormal(Globals::resources["icon_back_left_" + strColor]);
    msb->update(Globals::resources["icon_music_" + strColor]);
    ssb->update(Globals::resources["icon_sfx_" + strColor]);
    forceBox->update(Globals::resources["icon_forcetouch_" + strColor]);
    settingsLabel->setColor(color);
    copyright->setColor(color);
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
