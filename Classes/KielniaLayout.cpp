//
//  KielniaLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 17/06/2017.
//
//

#include "KielniaLayout.hpp"

USING_NS_CC;
KielniaLayout::KielniaLayout() : inAnimation(false)
{
    
}

KielniaLayout::~KielniaLayout()
{
    
}

KielniaLayout* KielniaLayout::createWithSize(cocos2d::Size size, cocos2d::Color3B color, int kielnias, GameHandler* handler)
{
    KielniaLayout * ret = new (std::nothrow) KielniaLayout();
    if (ret && ret->initWithSize(size, color, kielnias, handler))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool KielniaLayout::initWithSize(cocos2d::Size size, cocos2d::Color3B& color, int kielnias, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            if(this->getPositionY() == 0 && this->isEnabled() && this->isVisible() && this->getOpacity() >= 255)
            {
                this->gameHandler->onNoThanksClicked();
            }
        }
    };
    
    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    const Vec2 pos(320, 652);
    const Vec2 remainingNumberPos(320, 204);
    const Vec2 surePos(177, 346);
    const Vec2 noThanksPos(450, 346);
    const Vec2 continueLabelPos(320, 969);
    const Vec2 remainingLabelPos(320, 133);
    
    body = Sprite::create(Globals::resources["kielnia_popup_body"]);
    body->setPosition(pos);
    addChild(body);
    
    shine = Sprite::create(Globals::resources["kielnia_popup_shine"]);
    shine->setPosition(pos);
    shine->runAction(RepeatForever::create(RotateBy::create(3.0, 360)));
    addChild(shine);
    
    timerSprite = Sprite::create(Globals::resources["kielnia_popup_timer"]);
    timer = ProgressTimer::create(timerSprite);
    timer->setType(cocos2d::ProgressTimer::Type::RADIAL);
    timer->setPosition(pos);
    timer->setPercentage(100.0f);
    timer->setRotation3D(Vec3(0, 180, 0));
    addChild(timer);
    
    kielniasRemaining = Label::createWithTTF(StringUtils::format("%d", kielnias), Globals::gameFont, 118);
    kielniasRemaining->setColor(Color3B(244, 190, 113));
    kielniasRemaining->setPosition(remainingNumberPos);
    addChild(kielniasRemaining);
    
    kielniasRemainingSecond = Label::createWithTTF(StringUtils::format("%d", kielnias - 1), Globals::gameFont, 118);
    kielniasRemainingSecond->setColor(Color3B(244, 190, 113));
    kielniasRemainingSecond->setPosition(remainingNumberPos);
    kielniasRemainingSecond->setVisible(false);
    addChild(kielniasRemainingSecond);
    
    
    sure = SHButton::create(gameHandler, Globals::resources["kielnia_popup_sure"]);
    sure->setPosition(surePos);
    addChild(sure);
    
    
    noThanksLabel = Label::createWithTTF("No, thanks", Globals::gameFont, 42);
    noThanksLabel->setColor(color);
    //noThanksLabel->setPosition(noThanksPos);
    //addChild(noThanksLabel);
    
    
    noThanks = SHButton::create(gameHandler, "");
    noThanks->setTitleLabel(noThanksLabel);
    noThanks->setContentSize(Size(222, 150));
    noThanks->setPosition(noThanksPos);
    addChild(noThanks);
    
    continueLabel = Label::createWithTTF("CONTINUE?", Globals::gameFont, 66.0);
    continueLabel->setPosition(continueLabelPos);
    continueLabel->setColor(color);
    addChild(continueLabel);
    
    
    remainingLabel = Label::createWithTTF("REMAINING", Globals::gameFont, 30.0);
    remainingLabel->setPosition(remainingLabelPos);
    remainingLabel->setColor(color);
    addChild(remainingLabel);
    
   /* const Vec2 removeLabelPos(400, 200);
    removeLabel = Label::createWithTTF("-1", Globals::gameFont, 60);
    removeLabel->setColor(Color3B(199,57,60));
    removeLabel->setPosition(removeLabelPos);
    addChild(removeLabel);*/
    
    
    
    sure->addClickEventListener([this](Ref* sender){
        if(inAnimation) return;
        
        inAnimation = true;
        playClickSound();
        int kielnias = gameHandler->getKielnias();
        kielniasRemaining->setString(StringUtils::format("%d", kielnias - 1));
        kielniasRemaining->setOpacity(0);
        
        kielniasRemainingSecond->setString(StringUtils::format("%d", kielnias));
        kielniasRemainingSecond->setOpacity(255);
        kielniasRemainingSecond->setVisible(true);
        
        auto func = CallFunc::create([this](){
            kielniasRemainingSecond->setVisible(false);
            kielniasRemainingSecond->setScale(1.0);
            inAnimation = false;
            this->gameHandler->onKielniaUsed();
        });
        
        auto seq = Sequence::create(FadeIn::create(0.5), DelayTime::create(0.3), func, NULL);
        kielniasRemaining->runAction(seq);
        kielniasRemainingSecond->runAction(Sequence::create(ScaleTo::create(0.3, 2.0), FadeOut::create(0.3), NULL));
        
        //
    });
    
    noThanks->addClickEventListener([this](Ref* sender){
        this->gameHandler->onNoThanksClicked();
    });
    
    return true;
}



void KielniaLayout::setOpacity(GLubyte opacity)
{
    super::setOpacity(opacity);
    timer->setOpacity(opacity);
}

void KielniaLayout::launchTimer()
{
    stopActionByTag(101);
    timer->stopAllActions();
    timer->setPercentage(100);
    timer->runAction(ProgressTo::create(6.0, 0));
    
    auto func = CallFunc::create([this](){
        if(this->isVisible() && this->isEnabled())
        {
            this->gameHandler->onNoThanksClicked();
        }
    });
    auto seq = Sequence::create(DelayTime::create(6.0), func, NULL);
    seq->setTag(101);
    runAction(seq);
}

void KielniaLayout::setEnabled(bool enabled)
{
    super::setEnabled(enabled);
    if(!enabled)
    {
        stopActionByTag(101);
    }
}

void KielniaLayout::updateUI(Color3B color, int kielnias)
{
    kielniasRemaining->setString(StringUtils::format("%d", kielnias));
    continueLabel->setColor(color);
    noThanksLabel->setColor(color);
    remainingLabel->setColor(color);
}
