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
    
public:
    InfectionStop();
    virtual ~InfectionStop();
    
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    
    
};

#endif /* InfectionStop_hpp */
