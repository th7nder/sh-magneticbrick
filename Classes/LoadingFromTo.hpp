//
//  LoadingFromTo.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 17/10/2017.
//

#ifndef LoadingFromTo_hpp
#define LoadingFromTo_hpp


#include "cocos2d.h"

class LoadingFromTo : public cocos2d::ActionInterval
{
public:
    /**
     * @brief Create and initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @param duration Specify the duration of the LoadingFromTo action. It's a value in seconds.
     * @param fromPercentage Specify the source percentage.
     * @param toPercentage Specify the destination percentage.
     * @return If the creation success, return a pointer of LoadingFromTo action; otherwise, return nil.
     */
    static LoadingFromTo* create(float duration, float fromPercentage, float toPercentage);
    
    //
    // Overrides
    //
    virtual LoadingFromTo* clone() const override;
    virtual LoadingFromTo* reverse() const override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    virtual void update(float time) override;
    
CC_CONSTRUCTOR_ACCESS:
    LoadingFromTo() {}
    virtual ~LoadingFromTo() {}
    
    /**
     * @brief Initializes the action with a duration, a "from" percentage and a "to" percentage.
     * @param duration Specify the duration of the LoadingFromTo action. It's a value in seconds.
     * @param fromPercentage Specify the source percentage.
     * @param toPercentage Specify the destination percentage.
     * @return If the creation success, return true; otherwise, return false.
     */
    bool initWithDuration(float duration, float fromPercentage, float toPercentage);
    
protected:
    float _to;
    float _from;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(LoadingFromTo);
};



#endif /* LoadingFromTo_hpp */
