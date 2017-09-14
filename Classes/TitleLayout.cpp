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
    Color3B color = gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    createLogo();
    createPlayButton();
    createShopButton(color);
    createSettingsButton(color);
    createBricksRemaining(color);
    
    
    return true;
}


void TitleLayout::updateUI()
{
    playButton->loadTextureNormal(gameHandler->getLastTheme().getPlayButtonPath());
    
    if(gameHandler->getRemoveAds())
    {
        bricksRemainingLabel->setString("∞");
    }
    else
    {
        bricksRemainingLabel->setString(StringUtils::format("%d", gameHandler->getBricksRemaining()));
    }
    
    Color3B color = gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    shopButton->setColor(color);
    settingsButton->setColor(color);
    bricksRemainingLabel->setColor(color);
    bricksRemainingTitleLabel->setColor(color);
}


void TitleLayout::createLogo()
{
    const cocos2d::Vec2 pos(320, 786);
    logo = cocos2d::Sprite::create(Globals::resources["logo_mb"]);
    logo->setPosition(pos);

    
    addChild(logo);
}

void TitleLayout::createPlayButton()
{
    const cocos2d::Vec2 pos(320, 436);
    playButton = SHButton::create(gameHandler, ThemeManager::getInstance()->getTheme(gameHandler->getLastThemeId()).getPlayButtonPath());
    playButton->setPosition(pos);
    playButton->addClickEventListener(CC_CALLBACK_1(TitleLayout::onPlayButtonClicked, this));
    
    
    auto sequence = Sequence::create(ScaleTo::create(1, 1.15), ScaleTo::create(1, 1.0), NULL);
    auto action = RepeatForever::create(sequence);
    playButton->runAction(action);
    addChild(playButton);
}


void TitleLayout::createShopButton(const Color3B& color)
{

    shopButton = SHButton::create(gameHandler, Globals::resources["icon_cart_white"]);
    
    const cocos2d::Vec2 pos(90, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    shopButton->setPosition(pos);
    shopButton->addClickEventListener([this](Ref* sender)
                                      {
                                          this->gameHandler->onShopButtonClicked();
                                      });
    
    auto spawnFirst = Spawn::create(ScaleTo::create(1.0, 1.2), Sequence::create(RotateBy::create(0.5, -10), RotateBy::create(0.5, 10), NULL), NULL);
    auto spawnSecond = Spawn::create(ScaleTo::create(1.0, 1.0), Sequence::create(RotateBy::create(0.5, 10), RotateBy::create(0.5, -10), NULL), NULL);
    
    auto sequence = Sequence::create(spawnFirst, spawnSecond, NULL);
    auto action = RepeatForever::create(sequence);
    
    shopButton->runAction(action);
    shopButton->setColor(color);
    addChild(shopButton);
    
    
}
void TitleLayout::createSettingsButton(const Color3B& color)
{
    const cocos2d::Vec2 pos(550, Globals::getSmallPhone() ? 1056 - 30 : 1056);

    settingsButton = SHButton::create(gameHandler, Globals::resources["icon_settings_white"]);
    settingsButton->setColor(color);
    settingsButton->setPosition(pos);
    settingsButton->addClickEventListener(CC_CALLBACK_1(TitleLayout::onSettingsButtonClicked, this));
    
    auto firstRep = Repeat::create(RotateBy::create(1.0, 90), 6);
    auto secondRep = Repeat::create(RotateBy::create(1.0, -90), 6);
    auto sequence = Sequence::create(firstRep, secondRep, NULL);
    auto action = RepeatForever::create(sequence);
    
    
    settingsButton->runAction(action);
    addChild(settingsButton);
}

void TitleLayout::createBricksRemaining(const Color3B& color)

{
    Vec2 pos(320, 206);
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

///////////////// OVERRIDES

void TitleLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
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

///////////////// CALLBACKS
void TitleLayout::onSettingsButtonClicked(cocos2d::Ref *ref)
{
    gameHandler->onSettingsButtonClicked();
}

void TitleLayout::onPlayButtonClicked(cocos2d::Ref *ref)
{
    gameHandler->onPlayButtonClicked();
}

