//
//  LabelFromTo.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 17/10/2017.
//

#ifndef LabelFromTo_hpp
#define LabelFromTo_hpp

#include "cocos2d.h"

class LabelFromTo : public cocos2d::ActionInterval
{
public:
    /**
     * @brief Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @param duration Specify the duration of the LabelFromTo action. It's a value in seconds.
     * @param fromPercentage Specify the source percentage.
     * @param toPercentage Specify the destination percentage.
     * @return If the creation success, return a pointer of LabelFromTo action; otherwise, return nil.
     */
    static LabelFromTo* create(float duration, int from, int to);
    
    //
    // Overrides
    //
    virtual LabelFromTo* clone() const override;
    virtual LabelFromTo* reverse() const override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    LabelFromTo() {}
    virtual ~LabelFromTo() {}
    
    /**
     * @brief Initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @param duration Specify the duration of the LabelFromTo action. It's a value in seconds.
     * @param fromPercentage Specify the source percentage.
     * @param toPercentage Specify the destination percentage.
     * @return If the creation success, return true; otherwise, return false.
     */
    bool initWithDuration(float duration, int from, int to);
    
protected:
    int _to;
    int _from;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LabelFromTo);
};

#endif /* LabelFromTo_hpp */
