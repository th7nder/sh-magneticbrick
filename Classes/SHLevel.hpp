//
//  SHLevel.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 28/02/2017.
//
//

#ifndef SHLevel_hpp
#define SHLevel_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UIScrollView.h"
#include "ui/UIButton.h"

#include "Theme.hpp"

#include "SimpleAudioEngine.h"
#include "GameHandler.hpp"
#include "Globals.hpp"

#include "SHButton.hpp"


class SHLevel : public cocos2d::ui::Layout
{
    enum LevelState
    {
        Locked = 0,
        Unlockable,
        Unlocked,
        Playable,
        Completed
    };
    
    cocos2d::Vec2 coordinates[6];
    
    cocos2d::Vec2 numbersCoordinates[6];
    cocos2d::ui::Button* numbers[6];
    
    
    LevelState levelCompleted[6];
    typedef cocos2d::ui::Layout super;
    typedef SHLevel self;
    typedef cocos2d::ui::ScrollView parent;
    
    static void onLevelButtonClicked(cocos2d::Ref* ref);
    static void onLevelSelected(cocos2d::Ref* ref);
    parent* view;
    bool expanded;
    cocos2d::ui::Button* button;
    cocos2d::ui::Layout* bottomLayout;
    Theme theme;
    void createNumbers();
    void changeState();
    void startGame(int level);

    
    cocos2d::Sprite* stars[6];
    void createLvlStars();

    static bool inAction;
    
    LevelState levelState;
    
    std::string getIcon(int level, std::string color);
    LevelState getLevelState()
    {
        return levelState;
    }
    

    std::string getStateTexture();
CC_CONSTRUCTOR_ACCESS:
    SHLevel();
    virtual ~SHLevel();
public:
    int themeId;
    GameHandler* gameHandler;
    cocos2d::Size getBottomLayoutContentSize()
    {
        return bottomLayout->getContentSize();
    }
    static SHLevel* create(parent* view, Theme theme, bool locked, GameHandler* gameHandler, int themeId);
    virtual bool init(parent* view, Theme theme, bool locked, GameHandler* gameHandler, int themeId);
    void updateLevel(int level);
    void updateTheme();
};

#endif /* SHLevel_hpp */
