//
//  RewardPopup.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 16/10/2017.
//

#include "RewardPopup.hpp"
#include "WinLoseLayout.hpp"

USING_NS_CC;
RewardPopup::RewardPopup() : bg(nullptr), chapter(false), isRemoving(false)
{
    
}

RewardPopup::~RewardPopup()
{
    
}



RewardPopup* RewardPopup::create(GameHandler *gameHandler, const std::string &icon, int lowValue, int highValue, int prevValue, bool chapter)
{
    RewardPopup * ret = new (std::nothrow) RewardPopup();
    if (ret && ret->init(gameHandler, icon, lowValue, highValue, prevValue, chapter))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}


bool RewardPopup::init(GameHandler *gameHandler, const std::string &icon, int lowValue, int highValue, int prevValue, bool chapter)
{
    setCascadeOpacityEnabled(true);
 
    if(!super::init()) return false;
    this->lowValue = lowValue;
    this->highValue = highValue;
    this->chapter = chapter;
    this->prevValue = prevValue;
    setAnchorPoint(Vec2(0.5, 0.5));
    createBackground();
    
    float percent = prevValue / static_cast<double>(highValue);
    percent *= 100.0;
    createLoadingBar(percent);
    createIcon(icon);
    createAmountLabel();
    
    
   setTouchEnabled(true);
    return true;
}

bool RewardPopup::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unusedEvent)
{
    if(!isRemoving)
    {
        isRemoving = true;
        runAction(Sequence::create(FadeOut::create(0.3), RemoveSelf::create(), NULL));
        ((WinLoseLayout*)getParent())->decPopupCount();
    }
    
    return true;
}

void RewardPopup::createIcon(std::string source)
{
    
    if(chapter)
    {
        item = Sprite::create(source);
        item->setAnchorPoint(Vec2::ZERO);
        auto currSize = item->getContentSize() * 0.3;
        Vec2 pos = getContentSize() / 2;
        pos.x -= currSize.width / 2;
        item->setScale(0.3);
        item->setPosition(Vec2(0, 0));
        currSize.height = 76.0;
        auto clipNode = createRoundedRectMaskNode(currSize, 10.0, 3.0f, 10);
        clipNode->setAnchorPoint(Vec2(0.5, 0.5));
        clipNode->setPosition(pos);
        addChild(clipNode);
        clipNode->addChild(item);
        clipNode->setCascadeOpacityEnabled(true);
    }
    else
    {
        item = Sprite::create(source);
        Vec2 pos = getContentSize() / 2;
        pos.y += 30.0;
        item->setPosition(pos);
        addChild(item);
    }
    
}

void RewardPopup::launch()
{
    float nextPercent = (lowValue / static_cast<float>(highValue)) * 100.0;
    bar->runAction(LoadingFromTo::create(1.0, bar->getPercent(), nextPercent));
    amountLabel->runAction(LabelFromTo::create(1.0, prevValue, lowValue));
}

void RewardPopup::createBackground()
{
    bg = Sprite::create(Globals::resources["shop_brick_at"]);
    bg->setOpacity(240);
    setContentSize(bg->getContentSize());
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    addChild(bg);
    
}

void RewardPopup::createLoadingBar(float percent)
{
    bar = ui::LoadingBar::create(Globals::resources["icon_progressbar_filled_white"]);
    bar->setPercent(percent);
    bar->setScale(0.5);
    
    Vec2 pos = getContentSize() / 2;
    pos.y -= 30.0;
    bar->setPosition(pos);
    addChild(bar);
    
    barSprite = Sprite::create(Globals::resources["icon_progressbar_stroke_white"]);
    barSprite->setScale(0.5);
    barSprite->setPosition(pos);
    addChild(barSprite);
}

void RewardPopup::createAmountLabel()
{
    

    
    
    
    restLabel = Label::createWithTTF(StringUtils::format("/%d", highValue), Globals::gameFont, 25.0);
    restLabel->setAnchorPoint(Vec2(0.5, 0.5));
    restLabel->setPosition(Vec2(getContentSize().width / 2 + 10, 30));
    addChild(restLabel);
    
    
    amountLabel = Label::createWithTTF(StringUtils::format("%d", prevValue), Globals::gameFont, 25.0);
    amountLabel->setAnchorPoint(Vec2(0.5, 0.5));
    amountLabel->setPosition(Vec2(restLabel->getPositionX() - (restLabel->getContentSize().width / 2) - (amountLabel->getContentSize().width / 2) - 1, 30));
    addChild(amountLabel);
    
    auto star = Sprite::create(Globals::resources["shop_bigstar_indicator_white"]);
    //star->setColor(Color3B::BLACK);
    star->setScale(0.30);
    star->setPosition(amountLabel->getPosition());
    
    star->setPositionX(restLabel->getPositionX() + amountLabel->getContentSize().width / 2 + star->getContentSize().width / 2 * 0.3 + 8);
    addChild(star);
}


void RewardPopup::appendCubicBezier(int startPoint, std::vector<Vec2>& verts, const Vec2& from, const Vec2& control1, const Vec2& control2, const Vec2& to, uint32_t segments)
{
    float t = 0;
    for(int i = 0; i < segments; i++)
    {
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        verts[startPoint + i] = Vec2(x,y);
        t += 1.0f / segments;
    }
}

ClippingNode* RewardPopup::createRoundedRectMaskNode(Size size, float radius, float borderWidth, int cornerSegments)
{
    const float kappa = 0.552228474;
    float oneMinusKappa = (1.0f-kappa);
    
    // define corner control points
    std::vector<Vec2> verts(16);
    
    verts[0] = Vec2(0, radius);
    verts[1] = Vec2(0, radius * oneMinusKappa);
    verts[2] = Vec2(radius * oneMinusKappa, 0);
    verts[3] = Vec2(radius, 0);
    
    verts[4] = Vec2(size.width - radius, 0);
    verts[5] = Vec2(size.width - radius * oneMinusKappa, 0);
    verts[6] = Vec2(size.width, radius * oneMinusKappa);
    verts[7] = Vec2(size.width, radius);
    
    verts[8] = Vec2(size.width, size.height - radius);
    verts[9] = Vec2(size.width, size.height - radius * oneMinusKappa);
    verts[10] = Vec2(size.width - radius * oneMinusKappa, size.height);
    verts[11] = Vec2(size.width - radius, size.height);
    
    verts[12] = Vec2(radius, size.height);
    verts[13] = Vec2(radius * oneMinusKappa, size.height);
    verts[14] = Vec2(0, size.height - radius * oneMinusKappa);
    verts[15] = Vec2(0, size.height - radius);
    
    // result
    std::vector<Vec2> polyVerts(4 * cornerSegments + 1);
    
    // add corner arc segments
    appendCubicBezier(0 * cornerSegments, polyVerts, verts[0], verts[1], verts[2], verts[3], cornerSegments);
    appendCubicBezier(1 * cornerSegments, polyVerts, verts[4], verts[5], verts[6], verts[7], cornerSegments);
    appendCubicBezier(2 * cornerSegments, polyVerts, verts[8], verts[9], verts[10], verts[11], cornerSegments);
    appendCubicBezier(3 * cornerSegments, polyVerts, verts[12], verts[13], verts[14], verts[15], cornerSegments);
    // close path
    polyVerts[4 * cornerSegments] = verts[0];
    
    // draw final poly into mask
    auto shapeMask = DrawNode::create();
    shapeMask->drawPolygon(&polyVerts[0], polyVerts.size(), Color4F::WHITE, 0.0f, Color4F::WHITE);
    
    // create clip node with draw node as stencil (mask)
    return ClippingNode::create(shapeMask);
}


