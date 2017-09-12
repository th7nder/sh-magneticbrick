//
//  ThemeManager.hpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 29/01/2017.
//
//

#ifndef ThemeManager_hpp
#define ThemeManager_hpp
#include "Theme.hpp"
class ThemeManager
{
private:
    std::vector<Theme> themes;
    ThemeManager();
public:
    static ThemeManager* getInstance();
    std::vector<Theme>& getThemes()
    {
        return themes;
    }
    Theme getTheme(int id) const;
};

#endif /* ThemeManager_hpp */
