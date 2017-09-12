//
//  RewardLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/06/2017.
//
//

#include "RewardLayout.hpp"

USING_NS_CC;
RewardLayout::RewardLayout() : chapterReward(nullptr), icon(nullptr)
{
    
}

RewardLayout::~RewardLayout()
{
    
}

RewardLayout* RewardLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    RewardLayout * ret = new (std::nothrow) RewardLayout();
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

bool RewardLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    createChapterReward();
    createBrickReward();
    return true;
}

void RewardLayout::createChapterReward()
{
    chapterReward = ui::Layout::create();
    chapterReward->setContentSize(getContentSize());
    chapterReward->setCascadeOpacityEnabled(true);
    chapterReward->setVisible(false);
    addChild(chapterReward);
    
    const Vec2 midPos(320, 568);
    chapterUnlocked = Sprite::create(Globals::resources["reward_chapter_unlocked"]);
    chapterUnlocked->setCascadeOpacityEnabled(true);
    chapterUnlocked->setPosition(midPos);
    chapterUnlocked->setScale(0);
    chapterReward->addChild(chapterUnlocked);
    
    
    chapterInfo = Sprite::create(Globals::resources["reward_chapter_info"]);
    chapterInfo->setPosition(Vec2(midPos));
    chapterInfo->setScale(0);
    chapterInfo->setCascadeOpacityEnabled(true);
    chapterReward->addChild(chapterInfo);
    
    chapterImg = Sprite::create(gameHandler->getLastTheme().getThumbnailUnlockedPath());
    chapterImg->setPosition(midPos);
    chapterInfo->addChild(chapterImg);
    
    
    
}

bool RewardLayout::launchChapterReward(int themeId)
{
    if(icon != nullptr)
    {
        removeChild(icon);
        icon = nullptr;
    }
    if(gameHandler->getLastThemeId() + 1 > 9) return false;
    setEnabled(true);
    setVisible(true);
    setOpacity(255);
    
    
    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_chapterunlocked"].c_str());
    chapterReward->setVisible(true);
    brickReward->setVisible(false);
    gameHandler->setThemeAvailable(themeId);
    gameHandler->updateUI();
    chapterImg->setTexture(gameHandler->getTheme(themeId).getThumbnailUnlockedPath());
    
    chapterUnlocked->setScale(0);
    chapterUnlocked->setOpacity(255);
    chapterInfo->setScale(0);
    chapterUnlocked->runAction(Sequence::create(ScaleTo::create(0.3, 1.0), DelayTime::create(1.5), FadeTo::create(0.3, 0), NULL));
    
    auto func = CallFunc::create([this](){
        this->setEnabled(false);
        this->setOpacity(255);
        this->setVisible(false);
        this->gameHandler->onChapterRewardEnded();
    });
    chapterInfo->runAction(Sequence::create(DelayTime::create(1.8), ScaleTo::create(0.3, 1.0), NULL));
    
    auto seq = Sequence::create(DelayTime::create(3.5), FadeOut::create(0.5), func, NULL);
    
    runAction(seq);
    
    return true;
}

void RewardLayout::createBrickReward()
{
    brickReward = ui::Layout::create();
    brickReward->setContentSize(getContentSize());
    brickReward->setCascadeOpacityEnabled(true);
    addChild(brickReward);
    
    const Vec2 midPos(320, 568);
    brickUnlocked = Sprite::create(Globals::resources["reward_brick_unlocked"]);
    brickUnlocked->setPosition(midPos);
    brickUnlocked->setScale(0);
    brickReward->addChild(brickUnlocked);
    
    
    brickBox = Sprite::create(Globals::resources["reward_brick_box"]);
    brickBox->setCascadeOpacityEnabled(true);
    brickBox->setPosition(Vec2(midPos));
    brickBox->setScale(0);
    brickReward->addChild(brickBox);
    
    
    auto func = [this](Ref* sender){
        brickReward->setEnabled(false);
        
        this->layerColor->runAction(Sequence::create(FadeIn::create(0.1), DelayTime::create(0.5), FadeOut::create(1.5), NULL));
        this->brickBox->runAction(Sequence::create(DelayTime::create(0.1), FadeOut::create(0), NULL));
        
        auto skins = SkinManager::getInstance()->getSkins();
        int size = (int)skins.size();
        int skin = 0;
        
        int bricksToUnlock = 0;
        int bricksArray[16] = {0};
        for(int i = 1; i < size; i++)
        {
            if(!skins[i].getAccess())
            {
                bricksArray[bricksToUnlock++] = i;
            }
        }
        // TO DO
        CCLOG("%d skins to unlock", bricksToUnlock);
        if(!bricksToUnlock) return;

        skin = random(0, bricksToUnlock - 1);
        CCLOG("skin randed: %d", bricksArray[skin]);
        skins[bricksArray[skin]].setAccess(true);
        this->icon = Sprite::create(skins[bricksArray[skin]].getIconPath());
        this->icon->setPosition(Vec2(320, 568));
        this->addChild(icon, 2);
        
        icon->setOpacity(0);
        icon->runAction(Sequence::create(DelayTime::create(0.1), FadeIn::create(0), NULL));

        
        
        auto x = CallFunc::create([this](){
            this->gameHandler->onBrickRewardEnded();
        });
        
        this->runAction(Sequence::create(DelayTime::create(3.6), x, NULL));
    };
    auto button = ui::Button::create(Globals::resources["reward_guess"]);
    button->setPosition(Vec2(320, 640));
    brickBox->addChild(button);
    button->addClickEventListener(func);
    
    button = ui::Button::create(Globals::resources["reward_guess"]);
    button->setPosition(Vec2(320, 525));
    brickBox->addChild(button);
    button->addClickEventListener(func);
    
    
    button = ui::Button::create(Globals::resources["reward_guess"]);
    button->setPosition(Vec2(320, 411));
    brickBox->addChild(button);
    button->addClickEventListener(func);
    
    
    layerColor = LayerColor::create(Color4B(255, 255, 255, 0), getContentSize().width, getContentSize().height);
    
    addChild(layerColor, 5);
    
}

bool RewardLayout::launchBrickReward()
{
    if(icon != nullptr)
    {
        removeChild(icon);
        icon = nullptr;
    }
    brickReward->setEnabled(true);
    brickReward->setVisible(true);
    chapterReward->setVisible(false);
    setOpacity(255);

    

    auto sae = CocosDenshion::SimpleAudioEngine::getInstance();
    sae->playEffect(Globals::resources["effect_brickunlocked"].c_str());

    brickUnlocked->setScale(0);
    brickUnlocked->setVisible(true);
    brickUnlocked->setOpacity(255);
    brickUnlocked->runAction(Sequence::create(ScaleTo::create(0.3, 1.0), NULL));
    brickBox->setScale(0);
    brickBox->setOpacity(255);

    
    auto func = CallFunc::create([this](){
        this->brickUnlocked->setVisible(false);
    });
    brickBox->runAction(Sequence::create(DelayTime::create(1.8), ScaleTo::create(0.3, 1.0), func, NULL));
    
    
    return true;
}
