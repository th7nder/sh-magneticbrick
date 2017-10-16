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

#include "SHSwitch.hpp"
#include "Globals.hpp"
#include "GameHandler.hpp"


class RewardPopup : public cocos2d::Node
{
    typedef cocos2d::Node super;
    GameHandler* gameHandler;
    
    int lowValue;
    int highValue;
CC_CONSTRUCTOR_ACCESS:
    RewardPopup();
public:
    virtual ~RewardPopup();
    static RewardPopup* create(GameHandler* gameHandler, const std::string& icon, int lowValue, int highValue);
    virtual bool init(GameHandler* gameHandler, const std::string& icon, int lowValue, int highValue);
    
};
#endif /* RewardPopup_hpp */
