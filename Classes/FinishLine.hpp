//
//  FinishLine.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 18/03/2017.
//
//

#ifndef FinishLine_hpp
#define FinishLine_hpp
#include "cocos2d.h"
#include "LevelObject.hpp"

class FinishLine : public LevelObject
{
private:
    typedef FinishLine self;
    typedef LevelObject super;
CC_CONSTRUCTOR_ACCESS:
    FinishLine();
public:
    virtual ~FinishLine();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override;
    
};

#endif /* FinishLine_hpp */
