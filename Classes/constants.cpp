//
//  constants.cpp
//  MagneticBrick
//
//  Created by Konrad Stepniak on 02/02/2017.
//
//

#ifndef _constants
#define _constants



enum
{
    kFilterCategoryLevel = 0x01,
    kFilterCategorySolidObject = 0x02,
    kFilterCategoryNonSolidObject = 0x04,
    kFilterCategoryPlayer = 0x08,
};

const float kPixelsPerMeter = 100.0f;
inline double pixelsToMeters(double x)
{
    return x / kPixelsPerMeter;
}

inline double metersToPixels(double x)
{
    return x * kPixelsPerMeter;
}

inline double lerp(double previous, double current, double alpha)
{
    return current * alpha + previous * ( 1.0 - alpha );
}
#endif
