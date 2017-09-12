//
//  TutorialLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/06/2017.
//
//

#include "TutorialLayout.hpp"

USING_NS_CC;
TutorialLayout::TutorialLayout() : forceControl(nullptr), normalControl(nullptr), player(nullptr)
{
    
}

TutorialLayout::~TutorialLayout()
{
    
}

TutorialLayout* TutorialLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    TutorialLayout * ret = new (std::nothrow) TutorialLayout();
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

bool TutorialLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    if(gameHandler->getForceTouchAvailable())
    {
        createForceControlTutorial();
    }
    else
    {
        createNormalControlTutorial();
    }
    
    createLevelTutorial();
    return true;
}


void TutorialLayout::createNormalControlTutorial()
{
    normalControl = ui::Layout::create();
    normalControl->setContentSize(getContentSize());
    normalControl->setCascadeOpacityEnabled(true);
    normalControl->setVisible(false);
    addChild(normalControl);
    
    
    createNormalFirst();
    createNormalSecond();
    createNormalThird();
    createNormalLast();
}

void TutorialLayout::createNormalFirst()
{
    normalFirst = ui::Layout::create();
    normalFirst->setContentSize(getContentSize());
    normalFirst->setCascadeOpacityEnabled(true);
    normalControl->addChild(normalFirst);
    
    auto img = Sprite::create(Globals::resources["tutorial_normal_first"]);
    img->setAnchorPoint(Vec2::ZERO);
    normalFirst->addChild(img);
    
}

void TutorialLayout::createNormalSecond()
{
    normalSecond = ui::Layout::create();
    normalSecond->setContentSize(getContentSize());
    normalSecond->setCascadeOpacityEnabled(true);
    normalSecond->setPositionX(getContentSize().width);
    normalControl->addChild(normalSecond);
    
    auto img = Sprite::create(Globals::resources["tutorial_normal_second"]);
    img->setAnchorPoint(Vec2::ZERO);
    normalSecond->addChild(img);
    
}

void TutorialLayout::createNormalThird()
{
    normalThird = ui::Layout::create();
    normalThird->setContentSize(getContentSize());
    normalThird->setCascadeOpacityEnabled(true);
    normalThird->setPositionX(getContentSize().width);
    normalControl->addChild(normalThird);
    
    auto img = Sprite::create(Globals::resources["tutorial_normal_third"]);
    img->setAnchorPoint(Vec2::ZERO);
    normalThird->addChild(img);
    
}

void TutorialLayout::createNormalLast()
{
    normalLast = ui::Layout::create();
    normalLast->setContentSize(getContentSize());
    normalLast->setPositionX(getContentSize().width);
    normalLast->setCascadeOpacityEnabled(true);
    normalControl->addChild(normalLast);
    
    auto img = Sprite::create(Globals::resources["tutorial_normal_last"]);
    img->setAnchorPoint(Vec2::ZERO);
    normalLast->addChild(img);
    
    
    const Vec2 buttonPos(320, 100);
    auto button = SHButton::create(gameHandler, Globals::resources["tutorial_letstry_white"]);
    button->setPosition(buttonPos);
    button->addClickEventListener([this](Ref * sender){
        this->gameHandler->onLetsTryClicked();
        player->removeFromParentAndCleanup(true);
    });
    normalLast->addChild(button);

    const Vec2 starPos(320, 692);
    auto star = Sprite::create(Globals::resources["icon_star_collect_white"]);
    star->setPosition(starPos);
    auto seq = Sequence::create(FadeTo::create(0.5, 10), FadeIn::create(0.3), DelayTime::create(0.4), NULL);
    star->runAction(RepeatForever::create(seq));
    normalLast->addChild(star);


}


void TutorialLayout::createForceControlTutorial()
{
    forceControl = ui::Layout::create();
    forceControl->setContentSize(getContentSize());
    forceControl->setCascadeOpacityEnabled(true);
    forceControl->setVisible(false);
    addChild(forceControl);
    
    createForceFirst();
    createForceSecond();
    createForceThird();
    createForceFourth();
    createForceLast();
}


void TutorialLayout::createForceFirst()
{
    forceFirst = ui::Layout::create();
    forceFirst->setContentSize(getContentSize());
    forceControl->addChild(forceFirst);
    forceFirst->setCascadeOpacityEnabled(true);
    
    auto img = Sprite::create(Globals::resources["tutorial_force_first"]);
    img->setAnchorPoint(Vec2::ZERO);
    forceFirst->addChild(img);
    
    
}


void TutorialLayout::createForceSecond()
{
    forceSecond = ui::Layout::create();
    forceSecond->setContentSize(getContentSize());
    forceSecond->setPositionX(getContentSize().width);
    forceControl->addChild(forceSecond);
    forceSecond->setCascadeOpacityEnabled(true);
    
    auto img = Sprite::create(Globals::resources["tutorial_force_second"]);
    img->setAnchorPoint(Vec2::ZERO);
    forceSecond->addChild(img);
    
}


void TutorialLayout::createForceThird()
{
    forceThird = ui::Layout::create();
    forceThird->setContentSize(getContentSize());
    forceThird->setPositionX(getContentSize().width);
    forceControl->addChild(forceThird);
    forceThird->setCascadeOpacityEnabled(true);
    
    auto img = Sprite::create(Globals::resources["tutorial_force_third"]);
    img->setAnchorPoint(Vec2::ZERO);
    forceThird->addChild(img);
    
    
}

void TutorialLayout::createForceFourth()
{
    forceFourth = ui::Layout::create();
    forceFourth->setContentSize(getContentSize());
    forceFourth->setPositionX(getContentSize().width);
    forceControl->addChild(forceFourth);
    forceFourth->setCascadeOpacityEnabled(true);
    
    auto img = Sprite::create(Globals::resources["tutorial_force_fourth"]);
    img->setAnchorPoint(Vec2::ZERO);
    forceFourth->addChild(img);
    
    
    
    const Vec2 buttonPos(320, 100);
    auto button = SHButton::create(gameHandler, Globals::resources["tutorial_next_white"]);
    button->setPosition(buttonPos);
    button->addClickEventListener([this](Ref* sender){
        this->forceFourth->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
        this->forceLast->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    });
    forceFourth->addChild(button);
}


void TutorialLayout::createForceLast()
{
    forceLast = ui::Layout::create();
    forceLast->setContentSize(getContentSize());
    forceLast->setPositionX(getContentSize().width);
    forceControl->addChild(forceLast);
    forceLast->setCascadeOpacityEnabled(true);
    
    auto img = Sprite::create(Globals::resources["tutorial_force_last"]);
    img->setAnchorPoint(Vec2::ZERO);
    forceLast->addChild(img);
    
    
    const Vec2 buttonPos(320, 100);
    auto button = SHButton::create(gameHandler, Globals::resources["tutorial_letstry_white"]);
    button->setPosition(buttonPos);
    button->addClickEventListener([this](Ref * sender){
        this->gameHandler->onLetsTryClicked();
        player->removeFromParentAndCleanup(true);
    });
    forceLast->addChild(button);
    
    const Vec2 starPos(320, 692);
    auto star = Sprite::create(Globals::resources["icon_star_collect_white"]);
    star->setPosition(starPos);
    auto seq = Sequence::create(FadeTo::create(0.5, 10), FadeIn::create(0.3), DelayTime::create(0.4), NULL);
    star->runAction(RepeatForever::create(seq));
    forceLast->addChild(star);

}


void TutorialLayout::firstStageCompleted()
{
    normalFirst->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    normalSecond->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
}

void TutorialLayout::secondStageCompleted()
{
    normalSecond->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    normalThird->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
}


void TutorialLayout::thirdStageCompleted()
{
    normalThird->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    normalLast->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
}

void TutorialLayout::firstForceStageCompleted()
{
    forceFirst->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    forceSecond->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
}

void TutorialLayout::secondForceStageCompleted()
{
    forceSecond->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    forceThird->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
}


void TutorialLayout::thirdForceStageCompleted()
{
    forceThird->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
    forceFourth->runAction(MoveBy::create(0.3, Vec2(-getContentSize().width, 0)));
}


void TutorialLayout::onTouchEnded(cocos2d::Touch *t, cocos2d::Event *unusedEvent)
{
    onTouchMoved(t, unusedEvent);
    
    if(controlTutorialStage == 2)
    {
        if(!timerStarted)
        {
            auto func = CallFunc::create([this]()
                                         {
                                             if(normalControl != nullptr)
                                             {
                                                 this->thirdStageCompleted();
                                             }
                                             else
                                             {
                                                 this->thirdForceStageCompleted();
                                             }
                                             controlTutorialStage++;
                                         });
            auto seq = Sequence::create(DelayTime::create(1.0), func, NULL);
            seq->setTag(300);
            runAction(seq);
            timerStarted = true;
        }
    }
}

void TutorialLayout::onTouchCancelled(cocos2d::Touch *t, cocos2d::Event *unusedEvent)
{
    onTouchMoved(t, unusedEvent);
    
    if(controlTutorialStage == 2)
    {
        if(!timerStarted)
        {
            auto func = CallFunc::create([this]()
                                         {
                                             if(normalControl != nullptr)
                                             {
                                                 this->thirdStageCompleted();
                                             }
                                             else
                                             {
                                                 this->thirdForceStageCompleted();
                                             }
                                             controlTutorialStage++;
                                         });
            auto seq = Sequence::create(DelayTime::create(1.0), func, NULL);
            seq->setTag(300);
            runAction(seq);
            timerStarted = true;
        }
    }
}

void TutorialLayout::onTouchMoved(cocos2d::Touch *t, cocos2d::Event *unusedEvent)
{
    switch(controlTutorialStage)
    {
        case 0:
        {
            if(std::abs(player->getSprite()->getPositionX() - 57) <= 17)
            {
                if(!timerStarted)
                {
                    auto func = CallFunc::create([this]()
                                                 {
                                                     if(normalControl != nullptr)
                                                     {
                                                         this->firstStageCompleted();
                                                     }
                                                     else
                                                     {
                                                         this->firstForceStageCompleted();
                                                     }
                                                     controlTutorialStage++;
                                                 });
                    auto seq = Sequence::create(DelayTime::create(1.0), func, NULL);
                    seq->setTag(100);
                    runAction(seq);
                    timerStarted = true;
                }
            }
            else
            {
                stopAllActionsByTag(100);
                timerStarted = false;
            }
            
            break;
        }
            
        case 1:
        {
            if(std::abs(player->getSprite()->getPositionX() - 162) <= 17)
            {
                if(!timerStarted)
                {
                    auto func = CallFunc::create([this]()
                                                 {
                                                     if(normalControl != nullptr)
                                                     {
                                                         this->secondStageCompleted();
                                                     }
                                                     else
                                                     {
                                                         this->secondForceStageCompleted();
                                                     }
                                                     controlTutorialStage++;
                                                 });
                    auto seq = Sequence::create(DelayTime::create(1.0), func, NULL);
                    seq->setTag(200);
                    runAction(seq);
                    timerStarted = true;
                }
            }
            else
            {
                stopAllActionsByTag(200);
                timerStarted = false;
            }
            
            break;
        }
            
        case 2:
        {
            if(std::abs(player->getSprite()->getPositionX() - 288) <= 17)
            {
                if(!timerStarted)
                {
                    auto func = CallFunc::create([this]()
                                                 {
                                                     if(normalControl != nullptr)
                                                     {
                                                         this->thirdStageCompleted();
                                                     }
                                                     else
                                                     {
                                                         this->thirdForceStageCompleted();
                                                     }
                                                     controlTutorialStage++;
                                                 });
                    auto seq = Sequence::create(DelayTime::create(1.0), func, NULL);
                    seq->setTag(300);
                    runAction(seq);
                    timerStarted = true;
                }
            }
            else
            {
                stopAllActionsByTag(300);
                timerStarted = false;
            }
            
            break;
        }
    }
}

void TutorialLayout::displayControl()
{
    setTouchEnabled(true);
    setSwallowTouches(false);
    controlTutorialStage = 0;
    gameHandler->setPlayerVelocities(0);
    bool force = false;
    if(normalControl != nullptr)
    {
        normalControl->setVisible(true);
    }
    else if(forceControl != nullptr)
    {
        forceControl->setVisible(true);
        force = true;
    }
    
    levelTutorial->setVisible(false);
    
    auto scale = _director->getContentScaleFactor();
    ValueMap props;
    props["x"] = 432.0f / scale;
    props["y"] = 426.0f / scale;
    props["initialSpeed"] = 300.0;
    props["tutorial"] = true;
    props["width"] = 216.0f / scale;
    props["height"] = 108.f / scale;
    
    player = Player::create(gameHandler, nullptr, nullptr);
    player->setProperties(props);
    player->addSprite();
    player->initPhysics(gameHandler->getWorld());
    player->setVelocities(0);
    gameHandler->setTutorialPlayer(player);
    if(force)
    {
        forceControl->addChild(player);
    }
    else
    {
        normalControl->addChild(player);
    }
}


void TutorialLayout::createLevelTutorial()
{
    levelTutorial = ui::Layout::create();
    levelTutorial->setContentSize(getContentSize());
    levelTutorial->setCascadeOpacityEnabled(true);
    levelTutorial->setVisible(false);
    addChild(levelTutorial);
    
    levelImg = Sprite::create(Globals::resources["tutorial_desert"]);
    levelImg->setAnchorPoint(Vec2::ZERO);
    levelTutorial->addChild(levelImg);
    
    const Vec2 buttonPos(320, 100);
    auto button = SHButton::create(gameHandler, Globals::resources["tutorial_letstry_white"]);
    button->setPosition(buttonPos);
    button->addClickEventListener([this](Ref * sender){
        this->gameHandler->onLetsTryClickedFromLevel();
    });
    levelTutorial->addChild(button);
}



void TutorialLayout::displayDesert()
{
    hideDefault();
    levelImg->setTexture(Globals::resources["tutorial_desert"]);
}

void TutorialLayout::displaySpace()
{
    hideDefault();
    levelImg->setTexture(Globals::resources["tutorial_space"]);
}

void TutorialLayout::displayWestern()
{
    hideDefault();
    levelImg->setTexture(Globals::resources["tutorial_western"]);
}

void TutorialLayout::displaySnowland()
{
    hideDefault();
    levelImg->setTexture(Globals::resources["tutorial_snowland"]);
}

void TutorialLayout::displayGraveyard()
{
    hideDefault();
    levelImg->setTexture(Globals::resources["tutorial_graveyard"]);
}

void TutorialLayout::displayMouth()
{
    hideDefault();
    levelImg->setTexture(Globals::resources["tutorial_mouth"]);
}

void TutorialLayout::hideDefault()
{
    setTouchEnabled(false);
    controlTutorialStage = -1;
    if(normalControl != nullptr)
    {
        normalControl->setVisible(false);
    }
    else if(forceControl != nullptr)
    {
        forceControl->setVisible(false);
    }
    
    levelTutorial->setVisible(true);
}
