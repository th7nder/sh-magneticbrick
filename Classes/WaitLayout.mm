//
//  WaitLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/05/2017.
//
//

#include "WaitLayout.hpp"
#include "TH7Bridge.hpp"

#if defined ADS
#include "PluginAdColony/PluginAdColony.h"
#include "PluginAdMob/PluginAdMob.h"
#include "PluginChartboost/PluginChartboost.h"
#endif

USING_NS_CC;
WaitLayout::WaitLayout() : back(nullptr), timer(nullptr), scheduleCount(0), seconds(nullptr), watchAd(nullptr), isCounting(false)
{
    
}

WaitLayout::~WaitLayout()
{
    
}

WaitLayout* WaitLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    WaitLayout * ret = new (std::nothrow) WaitLayout();
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


bool WaitLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    createBack();
    createTimer();
    createLabel();
    createButton();
    
    noInternetLabel = createNoInternetLabel(Vec2(320, 110));
    addChild(noInternetLabel);
    
    createBackButton();
    
    return true;
}

void WaitLayout::createButton()
{
    
    watchAd = SHButton::create(gameHandler, Globals::resources["watch_ad"]);
    watchAd->setPosition(Vec2(320, 286));
    watchAd->addClickEventListener([this](Ref* sender){

#if defined ADS
        if(TH7Bridge::isInternetAvailable())
        {

            if(gameHandler->getLastAdProvider() == "AdColony")
            {
                if(sdkbox::PluginAdMob::isAvailable("mb_video"))
                {
                    sdkbox::PluginAdMob::show("mb_video");
                    gameHandler->setLastAdProvider("AdMob");
                    pauseBackgroundMusic();
                    
                }
                else if(sdkbox::PluginAdColony::getStatus("video") == sdkbox::ADCOLONY_ZONE_STATUS_ACTIVE)
                {
                    sdkbox::PluginAdColony::show("video");
                    gameHandler->setLastAdProvider("AdColony");
                    pauseBackgroundMusic();
                }
                else if(sdkbox::PluginChartboost::isAvailable("Video"))
                {
                    sdkbox::PluginChartboost::show("Video");
                    gameHandler->setLastAdProvider("Chartboost");
                    pauseBackgroundMusic();
                }
                else
                {
                    noInternetLabel->setString("NO AD AVAILABLE");
                    fadeInOutLabel(noInternetLabel);
                    return;
                }
                
                
            } else if(gameHandler->getLastAdProvider() == "AdMob")
            {
                
                if(sdkbox::PluginChartboost::isAvailable("Video"))
                {
                    sdkbox::PluginChartboost::show("Video");
                    gameHandler->setLastAdProvider("Chartboost");
                    pauseBackgroundMusic();
                }
                else if(sdkbox::PluginAdColony::getStatus("video") == sdkbox::ADCOLONY_ZONE_STATUS_ACTIVE)
                {
                    sdkbox::PluginAdColony::show("video");
                    gameHandler->setLastAdProvider("AdColony");
                    pauseBackgroundMusic();
                }
                else if(sdkbox::PluginAdMob::isAvailable("mb_video"))
                {
                    sdkbox::PluginAdMob::show("mb_video");
                    gameHandler->setLastAdProvider("AdMob");
                    pauseBackgroundMusic();
                }
                else
                {
                    noInternetLabel->setString("NO AD AVAILABLE");
                    fadeInOutLabel(noInternetLabel);
                    return;
                }
            }
            else if(gameHandler->getLastAdProvider() == "Chartboost")
            {
                
                
                if(sdkbox::PluginAdColony::getStatus("video") == sdkbox::ADCOLONY_ZONE_STATUS_ACTIVE)
                {
                    sdkbox::PluginAdColony::show("video");
                    gameHandler->setLastAdProvider("AdColony");
                    pauseBackgroundMusic();
                }
                else if(sdkbox::PluginAdMob::isAvailable("mb_video"))
                {
                    sdkbox::PluginAdMob::show("mb_video");
                    gameHandler->setLastAdProvider("AdMob");
                    pauseBackgroundMusic();
                }
                else if(sdkbox::PluginChartboost::isAvailable("Video"))
                {
                    sdkbox::PluginChartboost::show("Video");
                    gameHandler->setLastAdProvider("Chartboost");
                    pauseBackgroundMusic();
                }
                else
                {
                    noInternetLabel->setString("NO AD AVAILABLE");
                    fadeInOutLabel(noInternetLabel);
                    return;
                }
            }
        }
        else
        {
            noInternetLabel->setString("NO INTERNET CONNETION");
            fadeInOutLabel(noInternetLabel);
            
            return;
        }
        


#endif
        this->gameHandler->onPlayerWaited(false);
    });
    addChild(watchAd);
}

void WaitLayout::pauseBackgroundMusic()
{
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    this->unscheduleAllCallbacks();
    if(sae->isBackgroundMusicPlaying())
    {
        sae->pauseBackgroundMusic();
    }
}

void WaitLayout::fadeInOutLabel(cocos2d::Label* label)
{
    if(label->isVisible()) return;
    label->setVisible(true);
    label->setOpacity(0);
    auto func = CallFunc::create([label]()
                                 {
                                     label->setVisible(false);
                                 });
    
    auto seq = Sequence::create(FadeIn::create(0.3), FadeOut::create(0.3), FadeIn::create(0.3), FadeOut::create(0.3), FadeIn::create(0.3), DelayTime::create(3.0), FadeOut::create(0.3), func, NULL);
    label->runAction(seq);
}

void WaitLayout::createLabel()
{
    seconds = Label::createWithTTF(StringUtils::format("%d seconds", Globals::timeToWait), Globals::gameFont, 47.0);
    seconds->setPosition(Vec2(320, 436));
    seconds->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    addChild(seconds);
    
}

void WaitLayout::createBack()
{
    back = Sprite::create(Globals::resources["waitscreen_" + gameHandler->getLastTheme().getElementsColor()]);
    back->setAnchorPoint(Vec2::ZERO);
    addChild(back);
}

void WaitLayout::createBackButton()
{
    auto size = getContentSize();
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    
    const Vec2 pos(58, Globals::getSmallPhone() ? 1026 - 30 : 1026);
    backButton = SHButton::create(gameHandler, Globals::resources["icon_back_left_" + strColor]);
    backButton->setPosition(pos);
    backButton->addClickEventListener([this](Ref* sender){
        gameHandler->onBackFromWait();
    });
    addChild(backButton);
    
}



void WaitLayout::createTimer()
{
    ball = Sprite::create(Globals::resources["icon_progressball_" + gameHandler->getLastTheme().getElementsColor()]);
    timer = ProgressTimer::create(ball);
    timer->setCascadeOpacityEnabled(true);
    timer->setType(cocos2d::ProgressTimer::Type::RADIAL);
    timer->setPosition(Vec2(320, 750));
    timer->setPercentage(100.0f);
    timer->setRotation3D(Vec3(0, 180, 0));
    addChild(timer);
    
}

void WaitLayout::update(float dt)
{
    if(Globals::timeToWait - scheduleCount < 0) return;
    if(Globals::timeToWait - scheduleCount == 0)
    {
        seconds->setString(StringUtils::format("%d seconds", Globals::timeToWait));
    }
    else
    {
        seconds->setString(StringUtils::format("%d seconds", Globals::timeToWait - scheduleCount++));
    }
    


}

void WaitLayout::launchTimer(int count)
{
    if(isCounting) return;
    seconds->setString(StringUtils::format("%d seconds", Globals::timeToWait));
    isCounting = true;
    scheduleCount = count;
    this->schedule(schedule_selector(WaitLayout::update), 1.0, Globals::timeToWait - count + 1, 0.0);
    auto func = CallFunc::create([this](){
        this->isCounting = false;
        this->gameHandler->onPlayerWaited(true);
    });
    
    Sequence* seq;
    if(count != 1)
    {
        float percent = (float(scheduleCount) / float(Globals::timeToWait)) * 100.0f;
        timer->setPercentage(100.0f - percent);
        seq = Sequence::create(ProgressTo::create(Globals::timeToWait - count + 1, 0), func, NULL);
    }
    else
    {
        seq = Sequence::create(ProgressFromTo::create(Globals::timeToWait, 100, 0), func, NULL);
    }
    
    seconds->setString(StringUtils::format("%d seconds", Globals::timeToWait - scheduleCount));
    timer->runAction(seq);
}
void WaitLayout::updateUI()
{
    auto strColor = gameHandler->getLastTheme().getElementsColor();
    back->setTexture(Globals::resources["waitscreen_" + strColor]);
    backButton->loadTextureNormal(Globals::resources["icon_back_left_" + strColor]);
    seconds->setColor(gameHandler->getLastTheme().isWhite() ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
    timer->removeFromParent();
    createTimer();
}

void WaitLayout::onGameExit()
{
    this->unscheduleAllCallbacks();
    timer->stopAllActions();
}

void WaitLayout::onGameEnter()
{
    auto ud = UserDefault::getInstance();
    double leftTime = ud->getDoubleForKey("leftAppTime");
    double enterTime = ud->getDoubleForKey("enterAppTime");
    double difference = enterTime - leftTime;
    if(!isCounting)
    {
        if(difference > Globals::timeToWait * 2 && gameHandler->getBricksRemaining() < 10)
        {
            gameHandler->setBricksRemaining(gameHandler->getBricksRemaining() + Globals::bricksAfterWaiting);
            gameHandler->updateUI();
        }
        return;
    }

    if(difference < 0) return;
    
    scheduleCount += (int)difference;
    
    if(scheduleCount > Globals::timeToWait)
    {
        gameHandler->onPlayerWaited(true);
    }
    else
    {
        launchTimer(scheduleCount);
    }
    
}

void WaitLayout::stopTimers()
{
    this->unscheduleAllCallbacks();
    this->timer->stopAllActions();
    isCounting = false;
}


void WaitLayout::setOpacity(GLubyte opacity)
{
    super::setOpacity(opacity);
    timer->setOpacity(opacity);
}

cocos2d::Label* WaitLayout::createNoInternetLabel(cocos2d::Vec2 pos)
{
    Label* label = Label::createWithTTF("NO INTERNET CONNECTION", Globals::gameFontBold, 35.0);
    label->setVisible(false);
    label->setPosition(pos);
    label->setColor(Color3B(199,57,60));
    return label;
}
