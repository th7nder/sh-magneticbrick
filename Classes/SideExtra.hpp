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
protected:
    std::string orientation;
    std::string texture;
public:
    SideExtra(const std::string& texture);
    virtual ~SideExtra();
    virtual int getZ() const override;
    
    virtual void addSprite() override;
    virtual void setProperties(cocos2d::ValueMap& props) override;
    
};


#endif /* SideExtra_hpp */
