//
//  SHLevel.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 28/02/2017.
//
//

#include "SHLevel.hpp"

USING_NS_CC;
bool SHLevel::inAction = false;

SHLevel::SHLevel() : expanded(false), button(nullptr), bottomLayout(nullptr), levelState(Locked), theme(Theme("", "", Color4B(1, 1, 1, 1), false))
{
    for(int i = 0; i < 6; i++)
    {
        levelCompleted[i] = Locked;
        numbers[i] = nullptr;
        stars[i] = nullptr;
    }
    
}

SHLevel::~SHLevel()
{
    
}


SHLevel* SHLevel::create(parent* view, Theme theme, bool locked, GameHandler* gameHandler, int themeId)
{
    SHLevel* ret = new (std::nothrow) SHLevel();
    if (ret && ret->init(view, theme, locked, gameHandler, themeId))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

void SHLevel::updateTheme()
{
    auto texture = getStateTexture();
    button->loadTextureNormal(texture);
    if(levelState == Locked)
    {
        button->setEnabled(false);
    } else if(levelState == Unlocked)
    {
        button->setEnabled(true);
    } else {
        button->setEnabled(true);
    }
    
    bottomLayout->setVisible(false);
    
    for(int i = 1; i <= 6; i++)
    {
        updateLevel(i);
    }
}


std::string SHLevel::getStateTexture()
{
    std::string texture;
    if(themeId > 0)
    {
        if(!gameHandler->isThemeAvailable(themeId) && gameHandler->isThemeAvailable(themeId - 1))
        {
            levelState = Unlockable;
            texture = theme.getThumbnailUnlockablePath();
        }
        else if(!gameHandler->isThemeAvailable(themeId - 1) && !gameHandler->isThemeAvailable(themeId))
        {
            levelState = Locked;
            texture = theme.getThumbnailLockedPath();
        }
        else
        {
            levelState = Unlocked;
            texture = theme.getThumbnailUnlockedPath();
        }
    }
    else
    {
        texture = theme.getThumbnailUnlockedPath();
        levelState = Unlocked;
    }
    
    
    return texture;
}

bool SHLevel::init(parent* view, Theme theme, bool locked, GameHandler* gameHandler, int themeId)
{
    if(!super::init()) return false;
    this->view = view;
    this->theme = theme;
    this->gameHandler = gameHandler;
    this->themeId = themeId;
    


    
    setCascadeOpacityEnabled(true);
    auto txt = getStateTexture();
    button = cocos2d::ui::Button::create(txt);
    button->loadTextureDisabled(txt);
    if(levelState == Locked)
    {
        button->setEnabled(false);
    }
    button->setContentSize(Size(640, 260)); // -1y
    button->setAnchorPoint(cocos2d::Vec2::ZERO);
    button->setPosition(cocos2d::Vec2::ZERO);
    button->addClickEventListener(onLevelButtonClicked);
    button->setSwallowTouches(true);
    

    

    auto bg = cocos2d::Sprite::create(theme.getThumbnailBackgroundPath());
    bg->setAnchorPoint(cocos2d::Vec2::ZERO);
    
    bottomLayout = cocos2d::ui::Layout::create();
    bottomLayout->setCascadeOpacityEnabled(true);
    bottomLayout->setAnchorPoint(cocos2d::Vec2::ZERO);
    bottomLayout->setContentSize(Size(640, 342)); // -1y
    
    bottomLayout->addChild(bg);
    bottomLayout->setEnabled(false);
    createNumbers();
    
    addChild(bottomLayout);
    addChild(button);
    setContentSize(button->getContentSize());
    
    bottomLayout->setVisible(false);
    
    coordinates[0] = Vec2(197, 241);
    coordinates[1] = Vec2(394, 241);
    coordinates[2] = Vec2(590, 241);
    coordinates[3] = Vec2(197, 105);
    coordinates[4] = Vec2(394, 105);
    coordinates[5] = Vec2(590, 105);
    createLvlStars();

    return true;
}


std::string SHLevel::getIcon(int level, std::string color)
{
    std::string icon;
    auto number = StringUtils::format("_%d", level);
    if(gameHandler->isLevelAvailable(themeId, level))
    {

        if(gameHandler->getLevelProgress(themeId, level) == 100)
        {
            icon = Globals::resources["icon_number_finished_" + color + number];
            levelCompleted[level - 1] = Completed;
        }
        else
        {
            icon = Globals::resources["icon_number_toplay_" + color + number];
            levelCompleted[level - 1] = Playable;
        }
        
    } else
    {
        levelCompleted[level - 1] = Locked;
        icon = Globals::resources["icon_number_toplay_" + color + number];
    }
    
    return icon;
}

void SHLevel::createLvlStars()
{
    for(int i = 1; i <= 6; i++)
    {
        if(gameHandler->isLevelAvailable(themeId, i))
        {
            stars[i - 1] = Sprite::create(Globals::resources[StringUtils::format("lvlmenu_stars_%d_", gameHandler->getStarsAt(themeId, i)) + (theme.getElementsColor())]);
            stars[i - 1]->setPosition(coordinates[i - 1]);
            bottomLayout->addChild(stars[i - 1]);
        }
    }
}



void SHLevel::createNumbers()
{
    const std::string color = theme.getElementsColor();

    numbersCoordinates[0] = Vec2(123, 241);
    numbersCoordinates[1] = Vec2(320, 241);
    numbersCoordinates[2] = Vec2(516, 241);
    numbersCoordinates[3] = Vec2(123, 106);
    numbersCoordinates[4] = Vec2(320, 106);
    numbersCoordinates[5] = Vec2(516, 106);
    
    for(int i = 1; i <= 6; i++)
    {
        numbers[i - 1] = cocos2d::ui::Button::create(getIcon(i, color));
        numbers[i - 1]->setPosition(numbersCoordinates[i - 1]);
        numbers[i - 1]->addClickEventListener(onLevelSelected);
        numbers[i - 1]->setTag(i);
        bottomLayout->addChild(numbers[i - 1]);
    }

    
}


void SHLevel::onLevelButtonClicked(cocos2d::Ref *ref)
{
    
    auto button = dynamic_cast<cocos2d::ui::Button*>(ref);
    if(button != nullptr)
    {
        auto shLevel = dynamic_cast<SHLevel*>(button->getParent());
        if(shLevel != nullptr)
        {

            switch(shLevel->getLevelState())
            {
                case Unlocked:
                {
                    playClickSound();
                    shLevel->changeState();
                    break;
                }
                    
                case Unlockable:
                {
                    shLevel->gameHandler->buyChapter(shLevel->themeId);
                    break;
                }
                    
                    
                default:
                {
                    
                }
            }

        }
    }
}

void SHLevel::onLevelSelected(cocos2d::Ref *ref)
{
    auto button = dynamic_cast<cocos2d::ui::Button*>(ref);
    if(button != nullptr)
    {
       
        auto shLevel = dynamic_cast<SHLevel*>(button->getParent()->getParent());
        if(shLevel != nullptr && shLevel->getLevelState() == Unlocked)
        {
            shLevel->startGame(button->getTag());
        }
    }
}

void SHLevel::startGame(int level)
{
    if(!gameHandler->getRemoveAds() && gameHandler->getBricksRemaining() < 1)
    {
        gameHandler->setPostEffectEnabled();
        gameHandler->onBricksMissingFromSelect();
        return;
    }
    gameHandler->onThemeAndLevelSelected(themeId, level);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    view->setAnchorPoint(Vec2(0.5, 0.5));
    view->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    view->setEnabled(false);
    auto spawn = cocos2d::Spawn::create(ScaleTo::create(0.4, 0.01), MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height / 2)), nullptr);
    auto func = CallFunc::create([this](){
        this->view->setAnchorPoint(Vec2::ZERO);
        this->view->setPosition(Vec2::ZERO);
        this->view->setScale(1.0);
        this->gameHandler->hideUI();
    });
    auto seq = Sequence::create(spawn, func, NULL);
    this->view->runAction(seq);

}

void SHLevel::changeState()
{
    if(inAction)
    {
        return;
    }
    bottomLayout->setVisible(true);
    
    inAction = true;
    auto parent = getParent();
    auto children = parent->getChildren();
    float amount = bottomLayout->getContentSize().height;

    auto levelSize = getContentSize();
    levelSize.height += expanded ? -bottomLayout->getContentSize().height : bottomLayout->getContentSize().height;
    setContentSize(levelSize);
    expanded = !expanded;
    
    button->setPositionY(levelSize.height - button->getContentSize().height);
    bool down = true;
    if(expanded)
    {
        float targetY = getPositionY() - bottomLayout->getContentSize().height;
        auto visibleSize = Director::getInstance()->getVisibleSize();
        // nie wiem jak to wyszło, ale :) :) :) :)
        float startContainerY = visibleSize.height - view->getInnerContainerSize().height;
        float currentDifference = view->getInnerContainerPosition().y + startContainerY;
        float bottom = startContainerY - currentDifference;
        if(targetY < bottom)
        {
            down = false;
        }
        
        setPositionY(targetY);
        bottomLayout->setPositionY(button->getPositionY());
        auto func = CallFunc::create([this](){
            bottomLayout->setEnabled(true);
        });
        
        auto seq = Sequence::create(MoveTo::create(0.3, Vec2(0, 0)), func, NULL);
        bottomLayout->runAction(seq);
        

        
    } else {
        setPositionY(getPositionY() + bottomLayout->getContentSize().height);
        bottomLayout->setPositionY(-bottomLayout->getContentSize().height);
        
        bottomLayout->setEnabled(false);
        
        auto func = CallFunc::create([this](){
            bottomLayout->setVisible(false);
        });

        
        auto seq = Sequence::create(MoveBy::create(0.3, Vec2(0, bottomLayout->getContentSize().height)), func, NULL);
        bottomLayout->runAction(seq);
        

    }
    

    bool shrinking = false;
    for(auto child : children)
    {
        auto otherLevel = static_cast<SHLevel*>(child);
        if(otherLevel == this)
        {
            continue;
        }
        
        if(otherLevel->expanded)
        {
            shrinking = true;
            otherLevel->expanded = false;
            otherLevel->runAction(MoveBy::create(0.3, Vec2(0, bottomLayout->getContentSize().height)));
            //otherLevel->setPositionY(otherLevel->getPositionY() + bottomLayout->getContentSize().height);
            otherLevel->setContentSize(Size(button->getContentSize()));
            //otherLevel->button->setPositionY(0);
            otherLevel->bottomLayout->setPositionY(0);
            otherLevel->button->runAction(MoveTo::create(0.3, Vec2::ZERO));
            down = true;
            if(otherLevel->themeId > themeId)
            {
                for(auto nestedChild : children)
                {
                    auto otherNestedLevel = static_cast<SHLevel*>(nestedChild);
                    if(otherNestedLevel == this || otherNestedLevel == otherLevel)
                    {
                        continue;
                    }
                    
                    if(otherNestedLevel->themeId > otherLevel->themeId)
                    {
                        otherNestedLevel->runAction(MoveBy::create(0.3, Vec2(0, bottomLayout->getContentSize().height)));
                        //otherNestedLevel->setPositionY(otherNestedLevel->getPositionY() + bottomLayout->getContentSize().height);
                    }
                }
            } else if(otherLevel->themeId < themeId)
            {
                for(auto nestedChild : children)
                {
                    auto otherNestedLevel = static_cast<SHLevel*>(nestedChild);
                    if(otherNestedLevel == otherLevel)
                    {
                        continue;
                    }
                    
                    if(otherNestedLevel->themeId > otherLevel->themeId)
                    {
                        otherNestedLevel->runAction(MoveBy::create(0.3, Vec2(0, bottomLayout->getContentSize().height)));
                    }
                }
            }
            

        }
        
        
        if(otherLevel->themeId > themeId)
        {
            otherLevel->runAction(MoveBy::create(0.3, Vec2(0, expanded ? -bottomLayout->getContentSize().height : bottomLayout->getContentSize().height )));
        }
        
        
    }
    
    
    if(expanded && !shrinking)
    {
        auto contSize = view->getInnerContainerSize();
        contSize.height += amount;
        view->getInnerContainer()->setContentSize(contSize);
        
        view->getInnerContainer()->setPositionY(view->getInnerContainer()->getPositionY() - amount);

        for(auto child : children)
        {
            child->setPositionY(child->getPositionY() + amount);
        }
    }
    else if(!expanded && !shrinking)
    {
        auto contSize = view->getInnerContainerSize();
        contSize.height -= amount;
        view->getInnerContainer()->setContentSize(contSize);
        view->getInnerContainer()->setPositionY(view->getInnerContainer()->getPositionY() + amount);
        for(auto child : children)
        {
            child->setPositionY(child->getPositionY() - amount);
        }
        
        if(themeId > 5)
        {
            view->setTouchEnabled(false);
            view->runAction(Sequence::create(DelayTime::create(0.35),CallFunc::create([this](){this->view->setTouchEnabled(true);}),NULL));
            parent->runAction(MoveBy::create(0.3, Vec2(0, -amount)));
        }
    }
    
    
    if(!down && expanded)
    {
        parent->runAction(MoveBy::create(0.3, Vec2(0, bottomLayout->getContentSize().height)));
    }
    
    
    view->setTouchEnabled(false);
    auto seq = Sequence::create(DelayTime::create(0.3), CallFunc::create([this]{
            this->inAction = false;
        view->setTouchEnabled(true);
    }), nullptr);
    
    runAction(seq);

}

void SHLevel::updateLevel(int level)
{
    auto texture = getIcon(level, theme.getElementsColor());
    numbers[level - 1]->loadTextureNormal(texture);
    if(stars[level - 1] != nullptr)
    {
        stars[level - 1]->setTexture(Globals::resources[StringUtils::format("lvlmenu_stars_%d_", gameHandler->getStarsAt(themeId, level)) + (theme.getElementsColor())]);
    }
    else
    {
        stars[level - 1] = Sprite::create(Globals::resources[StringUtils::format("lvlmenu_stars_%d_", gameHandler->getStarsAt(themeId, level)) + (theme.getElementsColor())]);
        stars[level - 1]->setPosition(coordinates[level - 1]);
        bottomLayout->addChild(stars[level - 1]);

    }
 
}

