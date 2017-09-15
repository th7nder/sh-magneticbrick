//
//  SHSwitch.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#ifndef SHSwitch_hpp
#define SHSwitch_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"

class SHSwitch : public cocos2d::ui::Button
{
    typedef cocos2d::ui::Button super;
    std::string onImage;
    std::string offImage;
    bool isOn;
    
    ccWidgetClickCallback switchCallback;
CC_CONSTRUCTOR_ACCESS:
    SHSwitch() : isOn(false), switchCallback(nullptr)
    {
        
    }
public:
    
    static SHSwitch* create(const std::string& onImage, const std::string& offImage, bool state);
    virtual bool init(const std::string& onImage, const std::string& offImage, bool state);
    void onClick(cocos2d::Ref* ref);
    void setState(bool state);
    void update(const std::string& on, const std::string& off);
    void addSwitchListener(const ccWidgetClickCallback& callback);
    bool getState()
    {
        return isOn;
    }
};

#endif /* SHSwitch_hpp */
