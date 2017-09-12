//
//  InfectionStop.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 19/06/2017.
//
//

#ifndef InfectionStop_hpp
#define InfectionStop_hpp

#include "cocos2d.h"
#include "LevelObject.hpp"
class InfectionStop : public LevelObject
{
private:
    typedef LevelObject super;
    typedef InfectionStop self;
    
CC_CONSTRUCTOR_ACCESS:
    InfectionStop();
    virtual ~InfectionStop();
public:
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    virtual void launch() override;
    
    
};

#endif /* InfectionStop_hpp */
