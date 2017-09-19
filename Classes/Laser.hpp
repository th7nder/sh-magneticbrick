//
//  Laser.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#ifndef Laser_hpp
#define Laser_hpp

#include "cocos2d.h"
#include "LevelObject.hpp"

class Laser : public LevelObject
{
    typedef Laser self;
    typedef LevelObject super;

public:
    Laser();
    virtual ~Laser();
    static std::string leftTexture;
    static std::string centerTexture;
    static std::string rightTexture;

    virtual void addSprite() override;
    virtual void setProperties(cocos2d::ValueMap& properties) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override;
};

#endif /* Laser_hpp */
