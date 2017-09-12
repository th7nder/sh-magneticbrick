//
//  SHSlider.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/02/2017.
//
//

#include "SHSlider.hpp"


SHSlider* SHSlider::create(const std::string& barTextureName,
                 const std::string& normalBallTextureName,
                 TextureResType resType)
{
    SHSlider* widget = new (std::nothrow) SHSlider();
    if (widget && widget->init())
    {
        widget->loadBarTexture(barTextureName, resType);
        widget->loadSlidBallTextureNormal(normalBallTextureName, resType);
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool SHSlider::hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera *camera, cocos2d::Vec3* /*p*/) const
{
    cocos2d::Rect rect;
    rect.size = _slidBallNormalRenderer->getContentSize();
    rect.origin.x -= rect.size.width;
    rect.origin.y -= rect.size.height;
    rect.size.width *= 4.0;
    rect.size.height *= 4.0;
    auto w2l = _slidBallNormalRenderer->getWorldToNodeTransform();
    
    cocos2d::Rect sliderBarRect;
    sliderBarRect.size = this->_barRenderer->getContentSize();

    auto barW2l = this->_barRenderer->getWorldToNodeTransform();
    return isScreenPointInRect(pt, camera, w2l, rect, nullptr) || isScreenPointInRect(pt, camera, barW2l, sliderBarRect, nullptr);
}
