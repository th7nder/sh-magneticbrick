//
//  WaitLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/05/2017.
//
//

#ifndef WaitLayout_hpp
#define WaitLayout_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UIButton.h"

#include "SHButton.hpp"
#include "GameHandler.hpp"

//#include "ui/UIProgressTimer.h"
class WaitLayout : public cocos2d::ui::Layout
{
    typedef cocos2d::ui::Layout super;
    typedef WaitLayout self;
    
    bool isCounting;
    GameHandler* gameHandler;
    cocos2d::ProgressTimer* timer;
    cocos2d::Sprite* ball;
    cocos2d::Label* seconds;
    SHButton* watchAd;
    int scheduleCount;
    
    cocos2d::ui::Layout* backLayout;
CC_CONSTRUCTOR_ACCESS:
    WaitLayout();
public:
    virtual std::string getDescription() const override
    {
        return "WaitLayout";
    }
    virtual ~WaitLayout();
    static self* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    
    cocos2d::Sprite* back;
    void createBack();
    void updateUI();
    void createTimer();
    void launchTimer(int count = 1);
    void createButton();
    
    virtual void update(float dt) override;
    
    void createLabel();
    
    
    void setBackTarget(cocos2d::ui::Layout* backTarget)
    {
        backLayout = backTarget;
    }
    
    cocos2d::ui::Layout* getBackTarget()
    {
        return backLayout;
    }
    
    
    virtual void setOpacity(GLubyte opacity) override;
    
    
    void onGameExit();
    void onGameEnter();
    
    void stopTimers();
    
    //////////////////////////////////////
    cocos2d::Label* noInternetLabel;
    cocos2d::Label* createNoInternetLabel(cocos2d::Vec2 pos);
    void fadeInOutLabel(cocos2d::Label* label);
    
    SHButton* backButton;
    void createBackButton();
    
    
    void pauseBackgroundMusic();
};


#endif /* WaitLayout_hpp */
