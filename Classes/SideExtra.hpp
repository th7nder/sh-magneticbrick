//
//  SideExtra.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 20/06/2017.
//
//

#ifndef SideExtra_hpp
#define SideExtra_hpp

#include "LevelObject.hpp"

class SideExtra : public LevelObject
{
private:
    typedef SideExtra self;
    typedef LevelObject super;
CC_CONSTRUCTOR_ACCESS:
    SideExtra();
    std::string orientation;
public:
    virtual int getZ() const override
    {
        return -1;
    }
    virtual ~SideExtra();
    static self* create(GameHandler* handler);
    virtual bool init(GameHandler* handler) override;
    

    virtual void initPhysics(b2World* world) override;
    virtual void setProperties(ValueMap& props) override;
    
};


#endif /* SideExtra_hpp */
