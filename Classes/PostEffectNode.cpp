//
//  PostEffectNode.cpp
//  WordsGame
//
//  Created by Mikhail Shulepov on 02/09/16.
//
//

#include "PostEffectNode.h"

USING_NS_CC;

#define OPT_DIVIDER 8
#define OPT_SCALE 0.125

PostEffectNode::~PostEffectNode() {

}

void PostEffectNode::setStaticDrawing(bool var) {
    staticDrawing = var;
    dirty = true;
}

bool PostEffectNode::getStaticDrawing() const {
    return staticDrawing;
}

void PostEffectNode::checkRenderTextures() {
    if (sizeDirty) {
        renderTextures.clear();
        rtSprites.clear();
        sizeDirty = false;
    }
    

    const size_t requiredRenderTextures = passes.size() + 2; //(staticDrawing ? 1 : 2);

    if (requiredRenderTextures != renderTextures.size()) {
        rtSprites.clear();
    }
    
    while (requiredRenderTextures < renderTextures.size()) {
        renderTextures.popBack();
    }
    
    
    if(requiredRenderTextures > renderTextures.size())
    {
        
        const Size size = getContentSize();
        RenderTexture *rt = RenderTexture::create(size.width, size.height);
        renderTextures.pushBack(rt);
        
        while (requiredRenderTextures - 1 > renderTextures.size()) {
            RenderTexture *rt = RenderTexture::create(size.width / OPT_DIVIDER , size.height / OPT_DIVIDER);
            renderTextures.pushBack(rt);
        }
        
        rt = RenderTexture::create(size.width / OPT_DIVIDER, size.height / OPT_DIVIDER);
        renderTextures.pushBack(rt);
        
    }

    if (rtSprites.empty()) {
        recreateRtSprites();
    }
}

void PostEffectNode::recreateRtSprites() {
    size_t pass = 0;
    int passNumber = 0;
    for (RenderTexture *rt: renderTextures) {
        Sprite *spr = Sprite::createWithTexture(rt->getSprite()->getTexture());
        spr->setAnchorPoint(Point::ZERO);
        spr->setBlendFunc(rt->getSprite()->getBlendFunc());
        
        spr->setOpacityModifyRGB(rt->getSprite()->isOpacityModifyRGB());
        spr->getTexture()->setAntiAliasTexParameters();
        
        
        if (pass && pass + 1 < renderTextures.size()) { // skip first and last
            spr->setGLProgramState(passes.at(passNumber));
            passNumber++;
        }
        spr->setFlippedY(true);
        rtSprites.pushBack(spr);
        pass += 1;
    }
}

void PostEffectNode::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) {
    if (!postEffectsEnabled || passes.empty() || _children.empty()) {
        Node::visit(renderer, parentTransform, parentFlags);
        return;
    }
    
    // quick return if not visible. children won't be drawn.
    if (!_visible)  {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    



    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    bool visibleByCamera = isVisitableByVisitingCamera();
    if (visibleByCamera) {
        draw(renderer, _modelViewTransform, flags);
        rtSprites.back()->visit(renderer, _modelViewTransform, flags);
    }

    
    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void PostEffectNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) {
    if (!postEffectsEnabled) {
        Node::draw(renderer, transform, flags);
        return;
    }
    
    if (!staticDrawing) {
        redraw(renderer, flags);
    } else if (shouldRedraw) {
        redraw(renderer, flags);
        shouldRedraw = false;
    }
}

void PostEffectNode::redraw(Renderer *renderer, uint32_t flags) {
    if (passes.empty() || _children.empty()) {
        return;
    }
    
    
    if (dirty) {
        checkRenderTextures();
        dirty = false;
    }


    RenderTexture *firstPass = renderTextures.front();
    firstPass->begin();
    sortAllChildren();
    for( int i = 0; i < _children.size(); i++ ) {
        auto node = _children.at(i);
        node->visit(renderer, _modelViewTransform, flags);
    }
    firstPass->end();
    rtSprites.front()->setScale(OPT_SCALE);
    

    for (size_t i = 1; i < renderTextures.size(); ++i) {
        Sprite *prevResult = rtSprites.at(i-1);
        
        RenderTexture *rt = renderTextures.at(i);
        rt->begin();
        prevResult->visit(renderer, _modelViewTransform, flags);
        rt->end();
    }
    
    rtSprites.back()->setScale(OPT_DIVIDER);
}

void PostEffectNode::setBlurRadius(float radius)
{
    
    int i = 0;
    for(const auto& pass : passes)
    {
        if(i <= 1)
        {
            pass->setUniformFloat("radius", radius / 1.5f );
        }
        else
        {
            pass->setUniformFloat("radius", radius);
        }

        i++;
    }
    
}
