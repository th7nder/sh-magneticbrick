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

#include "BaseLayout.hpp"


class SettingsLayout : public BaseLayout
{
private:
    typedef BaseLayout super;
    
    
    cocos2d::ui::Layout* backTarget;
    cocos2d::EventListenerKeyboard* keyboardListener;
    void createBackButton();
    void createMusicSliderBox();
    void createSfxSliderBox();
    void createForceBox();
    cocos2d::Label* createCopyright(cocos2d::Vec2 pos, float fontSize);
    cocos2d::Label* createSettingsLabel(cocos2d::Vec2 pos, float fontSize);
    


    void onBackButtonClicked(cocos2d::Ref* ref);
    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;
    
    GameHandler* gameHandler;

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
    void setBackTarget(cocos2d::ui::Layout* back);
    cocos2d::ui::Layout* getBackTarget()
    {
        return backTarget;
    }
    
    
    virtual void actionBackButton() override;
};

#endif /* SettingsLayout_hpp */
