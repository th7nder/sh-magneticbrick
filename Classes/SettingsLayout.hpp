//
//  SettingsLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#ifndef SettingsLayout_hpp
#define SettingsLayout_hpp





#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UIPageView.h"


#include "SHButton.hpp"
#include "SHSliderBox.hpp"
#include "SHSwitchBox.hpp"

#include "GameHandler.hpp"

#if defined ADS
#include "PluginIAP/PluginIAP.h"
#endif


class SettingsLayout : public cocos2d::ui::Layout
{
private:
    typedef cocos2d::ui::Layout super;
    

    cocos2d::ui::Layout* backTarget;
    cocos2d::EventListenerKeyboard* keyboardListener;
    SHButton* backButton;
    void createBackButton();
    
    SHSliderBox* msb;
    SHSliderBox* ssb;
    void createMusicSliderBox();
    void createSfxSliderBox();
    
    SHSwitchBox* forceBox;
    void createForceBox();
    
    static void onBackButtonClicked(cocos2d::Ref* ref);
    
    GameHandler* gameHandler;
    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;
    
    cocos2d::Label* copyright;
    cocos2d::Label* createCopyright(cocos2d::Vec2 pos, float fontSize);
    
    cocos2d::Label* settingsLabel;
    cocos2d::Label* createSettingsLabel(cocos2d::Vec2 pos, float fontSize);
    

CC_CONSTRUCTOR_ACCESS:
    SettingsLayout();
    virtual ~SettingsLayout();
public:
    virtual std::string getDescription() const override
    {
        return "SettingsLayout";
    }
    static SettingsLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
    void updateUI();
    void setBackTarget(cocos2d::ui::Layout* back);
    cocos2d::ui::Layout* getBackTarget()
    {
        return backTarget;
    }
    
};

#endif /* SettingsLayout_hpp */
