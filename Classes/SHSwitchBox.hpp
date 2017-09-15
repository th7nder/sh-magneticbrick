//
//  SHSwitchBox.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#ifndef SHSwitchBox_hpp
#define SHSwitchBox_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"

#include "SHSwitch.hpp"
#include "Globals.hpp"
#include "GameHandler.hpp"


class SHSwitchBox : public cocos2d::Node
{
    typedef cocos2d::Node super;
    cocos2d::ui::Button* leftButton;
    SHSwitch* shSwitch;
    GameHandler* gameHandler;
public:
    static SHSwitchBox* create(GameHandler* gameHandler, const std::string& leftImage, const float width);
    virtual bool init(GameHandler* gameHandler, const std::string& leftImage, const float width);
        void addSwitchListener(const SHSwitch::ccWidgetClickCallback& callback);
    void setState(bool state);
    void setEnabled(bool state);
    virtual void setColor(const cocos2d::Color3B &color) override;
};

#endif /* SHSwitchBox_hpp */
