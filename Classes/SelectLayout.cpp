//
//  SelectLayout.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 13/03/2017.
//
//

#include "SelectLayout.hpp"

USING_NS_CC;

SelectLayout::SelectLayout() : gameHandler(nullptr), keyboardListener(nullptr)
{
    
}

SelectLayout::~SelectLayout()
{
    _eventDispatcher->removeEventListener(keyboardListener);
}

SelectLayout* SelectLayout::createWithSize(cocos2d::Size size, GameHandler* handler)
{
    SelectLayout * ret = new (std::nothrow) SelectLayout();
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

bool SelectLayout::initWithSize(cocos2d::Size size, GameHandler* handler)
{
    if(!super::init()) return false;
    gameHandler = handler;
    setContentSize(size);
    
    setScrollBarEnabled(false);
    
    
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {

            if(this->getPositionY() == 0 && this->isEnabled() && this->getOpacity() >= 255)
            {
                this->gameHandler->onBackFromSelectSwiped();
            }
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    std::vector<Theme> themes = ThemeManager::getInstance()->getThemes();
    auto maxItems = themes.size();
    float maxSize = maxItems * 260;//+ level->getBottomLayoutContentSize().height;
    int i = 0;
    for(const auto& theme : themes)
    {
        auto level = SHLevel::create(this, theme, false, gameHandler, i);
        level->setTag(i);
        level->setPositionY(maxSize - (260 * (i + 1)));
        addChild(level, 10 - i);

        i++;
    }

    
    setInnerContainerSize(cocos2d::Size(size.width, maxSize));
    
    return true;
}


void SelectLayout::scrollChildren(const cocos2d::Vec2& deltaMove)
{
    super::scrollChildren(deltaMove);
    if(isEnabled() && deltaMove.y < -40.0f && (Director::getInstance()->getVisibleSize().height - getInnerContainerSize().height == getInnerContainerPosition().y))
    {
        gameHandler->onBackFromSelectSwiped();
    }
}

void SelectLayout::updateLevel(int theme, int level)
{
    SHLevel* shLevel = dynamic_cast<SHLevel*>(getChildByTag(theme));
    shLevel->updateLevel(level);
}

void SelectLayout::updateTheme(int theme)
{
    SHLevel* level = dynamic_cast<SHLevel*>(getChildByTag(theme));
    level->updateTheme();
    
}
