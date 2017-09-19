//
//  BulletTimeStart.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 01/06/2017.
//
//

#ifndef BulletTimeStart_hpp
#define BulletTimeStart_hpp

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Globals.hpp"
#include "LevelObject.hpp"
#include "SimpleAudioEngine.h"
class BulletTimeStart : public LevelObject
{
private:
    typedef LevelObject super;
    typedef BulletTimeStart self;
    
public:
    BulletTimeStart();
    virtual ~BulletTimeStart();

    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
    

};


#endif /* BulletTimeStart_hpp */
