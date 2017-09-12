//
//  WinLoseLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 26/05/2017.
//
//

#include "WinLoseLayout.hpp"
USING_NS_CC;

WinLoseLayout::WinLoseLayout() : replayButton(nullptr), backButton(nullptr), failedLabel(nullptr), bricksRemainingTitleLabel(nullptr), bricksRemainingLabel(nullptr)
{
    
}

WinLoseLayout::~WinLoseLayout()
{
    
}

WinLoseLayout* WinLoseLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    WinLoseLayout * ret = new (std::nothrow) WinLoseLayout();
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


bool WinLoseLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    createReplayButton();
    createPlayButton();
    createBackButton();
    createLabel();
    createBricksRemaining();
    createSettingsButton();
    createHomeButton();
    createLevelNumber();
    
    createStars();
    createKielnia();
    createKielniaLabel();
    createKielniaButton();
    
    createProgressLabel();
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            if(this->getPositionY() == 0 && this->isEnabled() && this->isVisible() && this->getOpacity() >= 255)
            {
                this->gameHandler->onBackFromLoseClicked();
            }
        }
    };
    
    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void WinLoseLayout::enableWidget(cocos2d::ui::Widget *w)
{
    w->setVisible(true);
    w->setTouchEnabled(true);
}

void WinLoseLayout::disableWidget(cocos2d::ui::Widget *w)
{
    w->setVisible(false);
    w->setTouchEnabled(false);

}

void WinLoseLayout::updateUI()
{
    if(gameHandler->getGameState() == GameHandler::Died)
    {
        failedLabel->setString("FAILED!");
        for(const auto& s : stars)
        {
            s->setVisible(false);
        }
        progressLabel->setVisible(true);
        progressLabel->setString(StringUtils::format("%d%%", gameHandler->getCurrentProgress()));
        
        enableWidget(replayButton);
        disableWidget(playButton);
    }
    else
    {
        for(const auto& s : stars)
        {
            s->setVisible(true);
        }
        failedLabel->setString("COMPLETED!");
        progressLabel->setVisible(false);
        
        enableWidget(playButton);
        disableWidget(replayButton);
    }
    auto color = gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0);
    auto stringColor = gameHandler->getLastTheme().getElementsColor();
    replayButton->loadTextureNormal(gameHandler->getLastTheme().getReplayButtonPath());
    playButton->loadTextureNormal(gameHandler->getLastTheme().getPlayButtonPath());
    backButton->loadTextureNormal(Globals::resources["icon_back_left_" + stringColor]);
    failedLabel->setColor(color);
    progressLabel->setColor(color);
    
    bricksRemainingLabel->setColor(color);
    if(gameHandler->getRemoveAds())
    {
        bricksRemainingLabel->setString("∞");
    }
    else
    {
        bricksRemainingLabel->setString(StringUtils::format("%d", gameHandler->getBricksRemaining()));
    }
    
    bricksRemainingTitleLabel->setColor(color);
    settingsButton->loadTextureNormal(Globals::resources["icon_settings_" + stringColor]);
    homeButton->loadTextureNormal(Globals::resources["icon_home_" + stringColor]);
    
    levelNumber->setColor(color);
    int lastTheme = gameHandler->getLastThemeId() + 1;
    int lastLevel = gameHandler->getLastLevelId();
    levelNumber->setString(StringUtils::format("%d-%d", lastTheme, lastLevel));
    

    updateStars();
    
    kielnia->setTexture(Globals::resources["icon_kielnia_" + stringColor]);
    kielniaLabel->setString(StringUtils::format("%d", gameHandler->getKielnias()));
}

void WinLoseLayout::updateStars()
{
    auto stringColor = gameHandler->getLastTheme().getElementsColor();
    int filledCount = 0;
    for(int i = 1; i <= 3; i++)
    {
        if(gameHandler->getStar(i)) filledCount++;
    }
    
    
    for(int i = 0; i < filledCount; i++)
    {
        stars[i]->setTexture(Globals::resources["icon_star_full_" + stringColor]);
    }
    
    for(int i = filledCount; i < 3; i++)
    {
        stars[i]->setTexture(Globals::resources["icon_star_empty_" + stringColor]);
    }
}

void WinLoseLayout::createReplayButton()
{
    const cocos2d::Vec2 pos(320, 436);
    replayButton = cocos2d::ui::Button::create(ThemeManager::getInstance()->getTheme(gameHandler->getLastThemeId()).getReplayButtonPath());
    replayButton->setPosition(pos);
    replayButton->addClickEventListener([this](Ref* sender){
        this->gameHandler->onReplayButtonClicked();
    });
    addChild(replayButton);
}

void WinLoseLayout::createPlayButton()
{
    const cocos2d::Vec2 pos(320, 436);
    playButton = cocos2d::ui::Button::create(ThemeManager::getInstance()->getTheme(gameHandler->getLastThemeId()).getPlayButtonPath());
    playButton->setPosition(pos);
    playButton->addClickEventListener([this](Ref* sender){
        this->gameHandler->onPlayNextButtonClicked();
    });
    addChild(playButton);
}


void WinLoseLayout::createBackButton()
{
    const Vec2 pos(90, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    backButton = SHButton::create(gameHandler, Globals::resources["icon_back_left_" + gameHandler->getLastTheme().getElementsColor()]);
    backButton->setPosition(pos);
    backButton->addClickEventListener([this](Ref* sender){
        this->gameHandler->onBackFromLoseClicked();
    });
    addChild(backButton);
    
}

void WinLoseLayout::createLevelNumber()
{
    const Vec2 pos(320, 931);
    int lastTheme = gameHandler->getLastThemeId() + 1;
    int lastLevel = gameHandler->getLastLevelId();
    levelNumber = Label::createWithTTF(StringUtils::format("%d-%d", lastTheme, lastLevel), Globals::gameFont, 40);
    levelNumber->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    levelNumber->setPosition(pos);
    addChild(levelNumber);
}

void WinLoseLayout::createLabel()
{
    const Vec2 pos(320, 866);
    failedLabel = Label::createWithTTF("FAILED!", Globals::gameFontBold, 80);
    failedLabel->setPosition(pos);
    failedLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    addChild(failedLabel);
}


void WinLoseLayout::createBricksRemaining()

{
    Vec2 pos(320, 206);
    bricksRemainingTitleLabel = Label::createWithTTF("BRICKS REMAINING:", Globals::gameFont, 30.0);
    bricksRemainingTitleLabel->setColor(Color3B(0, 0, 0));
    bricksRemainingTitleLabel->setPosition(pos);
    addChild(bricksRemainingTitleLabel);
    
    bricksRemainingLabel = Label::createWithTTF(StringUtils::format("%d", gameHandler->getBricksRemaining()), Globals::gameFontBold, 50);
    pos.y = 156;
    bricksRemainingLabel->setPosition(pos);
    bricksRemainingLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
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

void WinLoseLayout::createSettingsButton()
{
    settingsButton = SHButton::create(gameHandler, Globals::resources["icon_settings_" + gameHandler->getLastTheme().getElementsColor()]);
    const cocos2d::Vec2 pos(550, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    settingsButton->setPosition(pos);
    settingsButton->addClickEventListener([this](Ref* sender){
        this->gameHandler->onSettingsFromLoseClicked();
    });
    addChild(settingsButton);
}



void WinLoseLayout::createHomeButton()
{
    homeButton = SHButton::create(gameHandler, Globals::resources["icon_home_" + gameHandler->getLastTheme().getElementsColor()]);
    const cocos2d::Vec2 pos(320, Globals::getSmallPhone() ? 1056 - 30 : 1056);
    homeButton->setPosition(pos);
    homeButton->addClickEventListener([this](Ref* sender){
        this->gameHandler->onHomeFromLoseClicked();
    });
    addChild(homeButton);
}

void WinLoseLayout::createKielnia()
{
    auto stringColor = gameHandler->getLastTheme().getElementsColor();
    const Vec2 pos(200, 676);
    kielnia = Sprite::create(Globals::resources["icon_kielnia_" + stringColor]);
    kielnia->setPosition(pos);
    addChild(kielnia);
}

void WinLoseLayout::createKielniaLabel()
{
    const Vec2 pos(320, 676);
    auto color = Color3B(243, 190, 112);
    kielniaLabel = Label::createWithTTF(StringUtils::format("%d", gameHandler->getKielnias()), Globals::gameFontBold, 80.0);
    kielniaLabel->setColor(color);
    kielniaLabel->setPosition(pos);
    addChild(kielniaLabel);
}

void WinLoseLayout::createKielniaButton()
{
    const Vec2 pos(454, 676);
    kielniaButton = SHButton::create(gameHandler, Globals::resources["icon_kielnia_add"]);
    kielniaButton->setPosition(pos);
    kielniaButton->addClickEventListener([this](Ref* sender){
        this->gameHandler->onShopFromWinLose();
    });
    addChild(kielniaButton);
}


void WinLoseLayout::createStars()
{
    const Vec2 startLeftPos(220, 796);
    auto stringColor = gameHandler->getLastTheme().getElementsColor();
    int count = 0;
    for(int i = 0; i < 3; i++)
    {
        stars[i] = Sprite::create(Globals::resources["icon_star_full_" + stringColor]);
        stars[i]->setPosition(Vec2(startLeftPos.x + (count * 100), startLeftPos.y));
        addChild(stars[i]);
        count++;
    }
    
    updateStars();
}

void WinLoseLayout::createProgressLabel()
{
    const Vec2 pos(320, 791);
    progressLabel = Label::createWithTTF("0%", Globals::gameFont, 50);
    progressLabel->setPosition(pos);
    progressLabel->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    addChild(progressLabel);
    
}



void WinLoseLayout::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    
    if(isEnabled())
    {
        if(touch->getDelta().x < -50)
        {
            gameHandler->onSettingsFromLoseClicked();
        }
        else if(touch->getDelta().x > 50)
        {
            gameHandler->onBackFromLoseClicked();
        }
        else if(touch->getDelta().y < -50.0)
        {
            gameHandler->onHomeFromLoseClicked();
        }
    }
    
}
