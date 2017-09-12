//
//  SHSlider.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#ifndef SHSlider_hpp
#define SHSlider_hpp

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UISlider.h"

class SHSlider : public cocos2d::ui::Slider
{
    typedef cocos2d::ui::Slider super;
    virtual bool hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera* camera, cocos2d::Vec3 *p) const override;
public:
    static SHSlider* create(const std::string& barTextureName,
                            const std::string& normalBallTextureName,
                            TextureResType resType = TextureResType::LOCAL);
};

#endif /* SHSlider_hpp */
