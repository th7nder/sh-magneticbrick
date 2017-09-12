//
//  BlurFromTo.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 08/06/2017.
//
//

#ifndef BlurFromTo_hpp
#define BlurFromTo_hpp

#include "cocos2d.h"
#include "PostEffectNode.h"

#define kBlurFromToCast PostEffectNode*

class BlurFromTo : public cocos2d::ActionInterval
{
public:
    static BlurFromTo* create(float duration, float fromValue, float toValue);
    
    //
    // Overrides
    //
    virtual BlurFromTo* clone() const override;
    virtual BlurFromTo* reverse() const override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    BlurFromTo() {}
    virtual ~BlurFromTo() {}

    bool initWithDuration(float duration, float fromValue, float toValue);
    
protected:
    float _to;
    float _from;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(BlurFromTo);
};



#endif /* BlurFromTo_hpp */
