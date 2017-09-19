//
//  TutorialLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/06/2017.
//
//

#ifndef TutorialLayout_hpp
#define TutorialLayout_hpp


#include "cocos2d.h"

#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UIPageView.h"

#include "Globals.hpp"
#include "SHButton.hpp"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"
#include "Touchable.hpp"

#include "Player.hpp"

class TutorialLayout : public cocos2d::ui::Layout
{
private:
    Player* player;
    typedef cocos2d::ui::Layout super;
    typedef TutorialLayout self;
    GameHandler* gameHandler;


    cocos2d::ui::Layout* normalControl;
    void createNormalControlTutorial();
    cocos2d::ui::Layout* normalFirst;
    void createNormalFirst();
    
    cocos2d::ui::Layout* normalSecond;
    void createNormalSecond();
    
    cocos2d::ui::Layout* normalThird;
    void createNormalThird();
    
    cocos2d::ui::Layout* normalLast;
    void createNormalLast();
    
    
    cocos2d::ui::Layout* forceControl;
    cocos2d::Sprite* forceDots;
    void createForceControlTutorial();
    cocos2d::ui::Layout* forceFirst;
    void createForceFirst();
    
    cocos2d::ui::Layout* forceSecond;
    void createForceSecond();
    
    cocos2d::ui::Layout* forceThird;
    void createForceThird();
    
    cocos2d::ui::Layout* forceFourth;
    void createForceFourth();
    
    cocos2d::ui::Layout* forceLast;
    void createForceLast();
    
    
    cocos2d::ui::Layout* levelTutorial;
    cocos2d::Sprite* levelImg;
    void createLevelTutorial();

    int controlTutorialStage;
    bool timerStarted;
    
    void firstStageCompleted();
    void secondStageCompleted();
    void thirdStageCompleted();
    
    
    void firstForceStageCompleted();
    void secondForceStageCompleted();
    void thirdForceStageCompleted();
    
    virtual std::string getDescription() const override
    {
        return "TutorialLayout";
    }
CC_CONSTRUCTOR_ACCESS:
    TutorialLayout();
    virtual ~TutorialLayout();
public:
    static TutorialLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;
    virtual void onTouchEnded(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;
    virtual void onTouchCancelled(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;

    void displayDesert();
    
    void displaySpace();
    void displayWestern();
    void displaySnowland();
    void displayGraveyard();
    void displayMouth();
    void displayControl();
    
    
    void hideDefault();
    
};


#endif /* TutorialLayout_hpp */
