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

class TitleLayout : public cocos2d::ui::Layout
{
private:
    typedef cocos2d::ui::Layout super;
    typedef TitleLayout self;
    
    
    cocos2d::Sprite* logo;
    void createLogo();
    
    SHButton* playButton;
    void createPlayButton(const std::string& playImage);
    
    SHButton* shopButton;
    void createShopButton(const cocos2d::Color3B& color);
    
    SHButton* settingsButton;
    void createSettingsButton(const cocos2d::Color3B& color);
    
    
    cocos2d::Label* bricksRemainingTitleLabel;
    cocos2d::Label* bricksRemainingLabel;
    void createBricksRemaining(const cocos2d::Color3B& color, bool removeAds, int bricksRemaining);
    
    
    GameHandler* gameHandler;
// OVERRIDES
    virtual void onTouchMoved(cocos2d::Touch* t, cocos2d::Event* unusedEvent) override;
    
// CALLBACKS
    void onSettingsButtonClicked(cocos2d::Ref* ref);
    void onPlayButtonClicked(cocos2d::Ref* ref);
    void onShopButtonClicked(cocos2d::Ref* ref);

CC_CONSTRUCTOR_ACCESS:
    TitleLayout();
    virtual ~TitleLayout();
public:
    void updateRemainingBricks(bool removeAds, int bricksRemaining = 0);
    void updateUITheme(const cocos2d::Color3B& color, const std::string& playImage);
    static TitleLayout* createWithSize(cocos2d::Size size, GameHandler* handler, const cocos2d::Color3B& color, bool removeAds, int bricksRemaining, const std::string& playImage);
    virtual bool initWithSize(cocos2d::Size size, GameHandler* handler, const cocos2d::Color3B& color, bool removeAds, int bricksRemaining, const std::string& playImage);
};
#endif /* TitleLayout_hpp */
