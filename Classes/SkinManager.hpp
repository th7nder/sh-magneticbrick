//
//  SkinManager.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 12/06/2017.
//
//

#ifndef SkinManager_hpp
#define SkinManager_hpp

#include "Skin.hpp"
class SkinManager
{
    std::vector<Skin> skins;
    SkinManager();
public:
    ~SkinManager();
    static SkinManager* getInstance();
    Skin getSkin(int id);
    
    std::vector<Skin>& getSkins();
};

#endif /* SkinManager_hpp */
