//
//  SHButton.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 14/02/2017.
//
//

#include "SHButton.hpp"
USING_NS_CC;
SHButton* SHButton::create(GameHandler* gh, const std::string& normalImage,
                           const std::string& selectedImage,
                           const std::string& disableImage,
                           TextureResType texType)
{
    SHButton * ret = new (std::nothrow) SHButton();
    if (ret && ret->init(gh, normalImage, selectedImage, disableImage))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool SHButton::init(GameHandler* gh, const std::string& normalImage,
                    const std::string& selectedImage,
                    const std::string& disableImage,
                    TextureResType texType)
{
    gameHandler = gh;
    return cocos2d::ui::Button::init(normalImage, selectedImage, disableImage, texType);
}

bool SHButton::hitTest(const cocos2d::Vec2 &pt, const cocos2d::Camera* camera, cocos2d::Vec3 *p) const
{
    cocos2d::Rect rect;
    auto contentSize = getContentSize();
    if(contentSize.width < 170)
    {
        rect.size = contentSize * 4;
        rect.origin.x -= contentSize.width;
        rect.origin.y -= contentSize.height;
    }
    else
    {
        rect.size = contentSize;
    }
    return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
}




bool SHButton::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    _hitted = false;
    if (isVisible() && isEnabled() && isAncestorsEnabled() && isAncestorsVisible(this) )
    {
        _touchBeganPosition = touch->getLocation();
        auto camera = Camera::getVisitingCamera();
        if(hitTest(_touchBeganPosition, camera, nullptr))
        {
            if (isClippingParentContainsPoint(_touchBeganPosition)) {
                _hittedByCamera = camera;
                _hitted = true;
            }
        }
    }
    if (!_hitted)
    {
        return false;
    }
    setHighlighted(true);
    
    /*
     * Propagate touch events to its parents
     */
    if (_propagateTouchEvents)
    {
        this->propagateTouchEvent(TouchEventType::BEGAN, this, touch);
    }
    
    pushDownEvent();
    return true;
}

