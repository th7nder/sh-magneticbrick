//
//  TitleLayout.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/02/2017.
//
//

#ifndef TitleLayout_hpp
#define TitleLayout_hpp

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UIButton.h"
#include "ui/UIPageView.h"

#include "Globals.hpp"
#include "SHButton.hpp"

#include "ThemeManager.hpp"
#include "GameHandler.hpp"
#include "Touchable.hpp"
class TitleLayout : public cocos2d::ui::Layout
{
private:
    typedef cocos2d::ui::Layout super;
    typedef TitleLayout self;
    
    
    cocos2d::Sprite* logo;
    void createLogo();
    
    SHButton* playButton;
    void createPlayButton();
    
    SHButton* shopButton;
    void createShopButton(const Color3B& color);
    
    SHButton* settingsButton;
    void createSettingsButton(const Color3B& color);
    
    void createBricksRemaining(const Color3B& color);

    void onSettingsButtonClicked(cocos2d::Ref* ref);
    void onPlayButtonClicked(cocos2d::Ref* ref);
    
    cocos2d::Label* bricksRemainingTitleLabel;
    cocos2d::Label* bricksRemainingLabel;
    GameHandler* gameHandler;

    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;

CC_CONSTRUCTOR_ACCESS:
    TitleLayout();
    virtual ~TitleLayout();
public:
    void updateUI();
    static TitleLayout* createWithSize(cocos2d::Size size, GameHandler* handler);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler);
};
#endif /* TitleLayout_hpp */
