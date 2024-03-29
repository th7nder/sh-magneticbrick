//
//  RewardLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/06/2017.
//
//

#ifndef RewardLayout_hpp
#define RewardLayout_hpp


#include "cocos2d.h"

#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UIPageView.h"

#include "Globals.hpp"
#include "SHButton.hpp"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"
#include "Touchable.hpp"

class RewardLayout : public cocos2d::ui::Layout
{
private:
    typedef cocos2d::ui::Layout super;
    typedef RewardLayout self;
    GameHandler* gameHandler;
    
    
    ui::Layout* chapterReward;
    Sprite* chapterUnlocked;
    Sprite* chapterInfo;
    Sprite* chapterImg;
    void createChapterReward();
    
    LayerColor* layerColor;
    Sprite* icon;
    
    ui::Layout* brickReward;
    Sprite* brickUnlocked;
    Sprite* brickBox;
    
    void createBrickReward();
    
    
    
CC_CONSTRUCTOR_ACCESS:
    RewardLayout();
    virtual ~RewardLayout();
public:
    virtual std::string getDescription() const override
    {
        return "RewardLayout";
    }
    static RewardLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    
    bool launchChapterReward(int themeId);
    bool launchBrickReward();
};


#endif /* RewardLayout_hpp */
