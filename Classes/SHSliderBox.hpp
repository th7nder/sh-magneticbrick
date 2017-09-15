//
//  SHSliderBox.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#ifndef SHSliderBox_hpp
#define SHSliderBox_hpp

#include "cocos2d.h"
#include "SHButton.hpp"
#include "SHSlider.hpp"
#include "Globals.hpp"
#include "GameHandler.hpp"


class SHSliderBox : public cocos2d::Node
{
    typedef cocos2d::Node super;
    GameHandler* gameHandler;
    
    cocos2d::ui::Button* leftButton;
    SHButton*  minus;
    SHSlider* slider;
    SHButton*  plus;
    
    SHSlider::ccSliderCallback sliderCallback;
    int previousPercent;
    void setCallbacks();
protected:
    SHSliderBox();
public:
    static SHSliderBox* create(GameHandler* handler, const std::string& leftImage, const float width);
    virtual bool init(GameHandler* handler, const std::string& leftImage, const float width);
    virtual void setSliderCallback(const SHSlider::ccSliderCallback &callback);
    void setPercent(int percent);
    void setPreviousPercent(int percent);
    virtual void setColor(const cocos2d::Color3B &color) override;
};
#endif /* SHSliderBox_hpp */
