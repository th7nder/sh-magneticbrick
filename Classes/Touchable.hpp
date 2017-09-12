//
//  Touchable.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#ifndef Touchable_hpp
#define Touchable_hpp
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
class Touchable
{
public:
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* event) = 0;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* event) = 0;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* event) = 0;
    virtual void onTouchesCancelled(const std::vector<Touch*>& touches, Event* event) = 0;
};

#endif /* Touchable_hpp */
