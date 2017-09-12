//
//  TitleLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/02/2017.
//
//

#include "TitleLayout.hpp"
#include "Globals.hpp"
USING_NS_CC;


TitleLayout::TitleLayout() : logo(nullptr), bricksRemainingLabel(nullptr), gameHandler(nullptr), playButton(nullptr), shopButton(nullptr), settingsButton(nullptr), bricksRemainingTitleLabel(nullptr)
{

    
}

TitleLayout::~TitleLayout()
{
    
}

TitleLayout* TitleLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    TitleLayout * ret = new (std::nothrow) TitleLayout();
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

bool TitleLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    
    setContentSize(size);
    createLogo();
    createPlayButton();
    createShopButton();
    createSettingsButton();
    createBricksRemaining();
    


    return true;
}


void TitleLayout::updateUI()
{
    playButton->loadTextureNormal(gameHandler->getLastTheme().getPlayButtonPath());
    shopButton->loadTextureNormal(Globals::resources["icon_cart_" + gameHandler->getLastTheme().getElementsColor()]);
    settingsButton->loadTextureNormal(Globals::resources["icon_settings_" + gameHandler->getLastTheme().getElementsColor()]);
    bricksRemainingLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    if(gameHandler->getRemoveAds())
    {
        bricksRemainingLabel->setString("∞");
    }
    else
    {
        bricksRemainingLabel->setString(StringUtils::format("%d", gameHandler->getBricksRemaining()));
    }

    
    bricksRemainingTitleLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
}


void TitleLayout::createLogo()
{
    const cocos2d::Vec2 pos(320, 786);
    logo = cocos2d::Sprite::create(Globals::resources["logo_mb"]);
    logo->setPosition(pos);
    addChild(logo);
}

void TitleLayout::createPlayButton()
{//320 436
    const cocos2d::Vec2 pos(320, 436);
    playButton = SHButton::create(gameHandler, ThemeManager::getInstance()->getTheme(gameHandler->getLastThemeId()).getPlayButtonPath());
    playButton->setPosition(pos);
    playButton->addClickEventListener(TitleLayout::onPlayButtonClicked);
    addChild(playButton);
}


void TitleLayout::createShopButton()
{

    shopButton = SHButton::create(gameHandler, Globals::resources["icon_cart_" + gameHandler->getLastTheme().getElementsColor()]);
    const cocos2d::Vec2 pos(90, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    shopButton->setPosition(pos);
    shopButton->addClickEventListener([this](Ref* sender)
                                      {
                                          this->gameHandler->onShopButtonClicked();
                                      });
    addChild(shopButton);
    
    
}
void TitleLayout::createSettingsButton()
{
    settingsButton = SHButton::create(gameHandler, Globals::resources["icon_settings_" + gameHandler->getLastTheme().getElementsColor()]);
    const cocos2d::Vec2 pos(550, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    settingsButton->setPosition(pos);
    settingsButton->addClickEventListener(TitleLayout::onSettingsButtonClicked);
    addChild(settingsButton);
}

void TitleLayout::createBricksRemaining()

{
    Vec2 pos(320, 206);
    auto color = gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    bricksRemainingTitleLabel = Label::createWithTTF("BRICKS REMAINING:", Globals::gameFont, 30.0);
    bricksRemainingTitleLabel->setColor(color);
    bricksRemainingTitleLabel->setPosition(pos);
    addChild(bricksRemainingTitleLabel);
    
    bricksRemainingLabel = Label::createWithTTF(StringUtils::format("%d", gameHandler->getBricksRemaining()), Globals::gameFontBold, 50);
    pos.y = 156;
    bricksRemainingLabel->setPosition(pos);
    bricksRemainingLabel->setColor(color);
    addChild(bricksRemainingLabel);
    
    if(gameHandler->getRemoveAds())
    {
        bricksRemainingLabel->setString("∞");
    }
    else
    {
        bricksRemainingLabel->setString(StringUtils::format("%d", gameHandler->getBricksRemaining()));
    }
    
    
}

void TitleLayout::onSettingsButtonClicked(cocos2d::Ref *ref)
{
    auto button = dynamic_cast<SHButton*>(ref);
    if(button != nullptr)
    {
        auto titleLayout = dynamic_cast<TitleLayout*>(button->getParent());
        if(titleLayout != nullptr)
        {
             titleLayout->gameHandler->onSettingsButtonClicked();
        }
    }
}

void TitleLayout::onPlayButtonClicked(cocos2d::Ref *ref)
{
    auto button = dynamic_cast<cocos2d::ui::Button*>(ref);
    auto title = dynamic_cast<TitleLayout*>(button->getParent());
    if(title != nullptr)
    {
       title->gameHandler->onPlayButtonClicked();
    }
}

void TitleLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{

    if(!gameHandler->firstClick)
    {
        if(touch->getMaxForce() == 0.0)
        {
            gameHandler->setForceTouch(false);
            gameHandler->setForceTouchAvailable(false);
        } else
        {
            gameHandler->setForceTouchAvailable(true);
        }
        gameHandler->firstClick = true;
        gameHandler->onFirstClick();
    }
    
    if(isEnabled())
    {
        if(touch->getDelta().y > 50.0)
        {
            gameHandler->onPlayButtonClicked();
        } else if(touch->getDelta().x < -50)
        {
            gameHandler->onSettingsButtonClicked();
        } else if(touch->getDelta().x > 50)
        {
            gameHandler->onShopButtonClicked();
        }
    }

}
