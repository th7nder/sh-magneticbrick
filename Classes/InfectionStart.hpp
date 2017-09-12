//
//  InfectionStart.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef InfectionStart_hpp
#define InfectionStart_hpp

#include "cocos2d.h"
#include "LevelObject.hpp"
class InfectionStart : public LevelObject
{
private:
    typedef LevelObject super;
    typedef InfectionStart self;
    
CC_CONSTRUCTOR_ACCESS:
    InfectionStart();
    virtual ~InfectionStart();
public:
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    
    
};


#endif /* InfectionStart_hpp */
