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
#include "Globals.hpp"


class MeltingObstacle : public LevelObject
{
    typedef MeltingObstacle self;
    typedef LevelObject super;
    bool triggered;
CC_CONSTRUCTOR_ACCESS:
    MeltingObstacle();
    int size;
    std::string name;
    std::string centerTexture;
public:
    virtual ~MeltingObstacle();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void addSprite() override;
    virtual void setProperties(ValueMap& properties) override;
    virtual void addIce();
    virtual bool OnContactBegin(LevelObject* other, b2Body* body) override {return true;};
    
    virtual void launch() override;

};




#endif /* MeltingObstacle_hpp */
