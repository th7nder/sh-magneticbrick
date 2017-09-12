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


    ui::Layout* normalControl;
    void createNormalControlTutorial();
    ui::Layout* normalFirst;
    void createNormalFirst();
    
    ui::Layout* normalSecond;
    void createNormalSecond();
    
    ui::Layout* normalThird;
    void createNormalThird();
    
    ui::Layout* normalLast;
    void createNormalLast();
    
    
    ui::Layout* forceControl;
    Sprite* forceDots;
    void createForceControlTutorial();
    ui::Layout* forceFirst;
    void createForceFirst();
    
    ui::Layout* forceSecond;
    void createForceSecond();
    
    ui::Layout* forceThird;
    void createForceThird();
    
    ui::Layout* forceFourth;
    void createForceFourth();
    
    ui::Layout* forceLast;
    void createForceLast();
    
    
    ui::Layout* levelTutorial;
    Sprite* levelImg;
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
