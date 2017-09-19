//
//  BlackoutStop.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#ifndef BlackoutStop_hpp
#define BlackoutStop_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"
class BlackoutStop : public LevelObject
{
private:
    typedef LevelObject super;
    typedef BlackoutStop self;
    
public:
    BlackoutStop();
    virtual ~BlackoutStop();

    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    
};

#endif /* BlackoutStop_hpp */
