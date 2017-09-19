//
//  BlackoutStart.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#ifndef BlackoutStart_hpp
#define BlackoutStart_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"
class BlackoutStart : public LevelObject
{
private:
    typedef LevelObject super;
    typedef BlackoutStart self;
    
public:
    BlackoutStart();
    virtual ~BlackoutStart();
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    
    
};


#endif /* BlackoutStart_hpp */
