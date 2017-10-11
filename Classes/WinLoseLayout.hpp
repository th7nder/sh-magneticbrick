//
//  WinLoseLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 26/05/2017.
//
//

#ifndef WinLoseLayout_hpp
#define WinLoseLayout_hpp


#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UIButton.h"

#include "SHButton.hpp"
#include "GameHandler.hpp"

class WinLoseLayout : public cocos2d::ui::Layout
{
    typedef cocos2d::ui::Layout super;
    typedef WinLoseLayout self;
    
    GameHandler* gameHandler;
    cocos2d::ui::Button* replayButton;
    void createReplayButton();
    
    cocos2d::ui::Button* playButton;
    cocos2d::Label* nextLabel;
    void createPlayButton();
    
    SHButton* backButton;
    void createBackButton();
    
    cocos2d::Label* failedLabel;
    void createLabel();
    
    void createBricksRemaining();
    cocos2d::Label* bricksRemainingTitleLabel;
    cocos2d::Label* bricksRemainingLabel;
    
    SHButton* settingsButton;
    void createSettingsButton();
    
    SHButton* homeButton;
    void createHomeButton();
    
    cocos2d::Label* levelNumber;
    void createLevelNumber();
    
    
    cocos2d::Sprite* stars[3];
    void createStars();
    void updateStars();

    
    cocos2d::Sprite* kielnia;
    void createKielnia();
    
    cocos2d::Label* kielniaLabel;
    void createKielniaLabel();
    
    SHButton* kielniaButton;
    void createKielniaButton();
    
    cocos2d::Label* progressLabel;
    void createProgressLabel();
    
    void disableWidget(Widget* w);
    void enableWidget(Widget* w);
CC_CONSTRUCTOR_ACCESS:
    WinLoseLayout();
public:
    virtual std::string getDescription() const override
    {
        return "WinLoseLayout";
    }
    virtual ~WinLoseLayout();
    static self* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unusedEvent) override;
    
    void updateUI();
};

#endif /* WinLoseLayout_hpp */
