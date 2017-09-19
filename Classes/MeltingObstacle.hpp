//
//  MeltingObstacle.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 22/05/2017.
//
//

#ifndef MeltingObstacle_hpp
#define MeltingObstacle_hpp

#include "cocos2d.h"
#include "LevelObject.hpp"
#include "HorizontalObstacle.hpp"
#include "Globals.hpp"


class MeltingObstacle : public LevelObject
{
    typedef MeltingObstacle self;
    typedef LevelObject super;
    bool triggered;
    int size;
    std::string name;
public:
    MeltingObstacle();
    virtual ~MeltingObstacle();

    virtual void setProperties(cocos2d::ValueMap& properties) override;
    virtual void addSprite() override;

    virtual void addIce();
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override {return true;};
    

};




#endif /* MeltingObstacle_hpp */
