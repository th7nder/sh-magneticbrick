//
//  RewardPopup.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/10/2017.
//

#ifndef RewardPopup_hpp
#define RewardPopup_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UILoadingBar.h"

#include "SHSwitch.hpp"
#include "Globals.hpp"
#include "GameHandler.hpp"

#include "LoadingFromTo.hpp"
#include "LabelFromTo.hpp"


class RewardPopup : public cocos2d::ui::Widget
{
    typedef cocos2d::ui::Widget super;
    GameHandler* gameHandler;
    
    
    bool isRemoving;
    bool chapter;
    int prevValue;
    int lowValue;
    int highValue;
    
    cocos2d::Sprite* bg;
    void createBackground();
    
    cocos2d::Sprite* barSprite;
    
    cocos2d::ui::LoadingBar* bar;
    void createLoadingBar(float percent);
    
    cocos2d::Sprite* item;
    void createIcon(std::string source);
    
    cocos2d::Label* amountLabel;
    cocos2d::Label* restLabel;
    cocos2d::Sprite* star;
    void createAmountLabel();
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent);
    
    
    void appendCubicBezier(int startPoint, std::vector<cocos2d::Vec2>& verts, const cocos2d::Vec2& from, const cocos2d::Vec2& control1, const cocos2d::Vec2& control2, const cocos2d::Vec2& to, uint32_t segments);
    cocos2d::ClippingNode* createRoundedRectMaskNode(cocos2d::Size size, float radius, float borderWidth, int cornerSegments);
CC_CONSTRUCTOR_ACCESS:
    RewardPopup();
public:
    virtual ~RewardPopup();
    static RewardPopup* create(GameHandler* gameHandler, const std::string& icon, int lowValue, int highValue, int prevValue, bool chapter);
    virtual bool init(GameHandler* gameHandler, const std::string& icon, int lowValue, int highValue, int prevValue, bool chapter);
    
    void launch();
    
};
#endif /* RewardPopup_hpp */
