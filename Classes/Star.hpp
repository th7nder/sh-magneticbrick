//
//  Star.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 09/03/2017.
//
//

#ifndef Star_hpp
#define Star_hpp

#include "cocos2d.h"
#include "LevelObject.hpp"

class Level;
class Star : public LevelObject
{
private:
    typedef Star self;
    typedef LevelObject super;
    int number;
CC_CONSTRUCTOR_ACCESS:
    Star();
public:
    virtual std::string getDescription() const override
    {
        return "Star";
    }
    
    int getNumber() {return number;}
    virtual ~Star();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    virtual void setProperties(ValueMap& props) override;
    virtual void addSprite() override;
    virtual void initPhysics(b2World* world) override;
    virtual bool OnContactBegin(LevelObject* other, b2Body* otherBody) override;
    
};

#endif /* Star_hpp */
