#ifndef _CN_MATHEMATICS_
#define _CN_MATHEMATICS_
#include "Prerequisites.h"
#include <math.h>

namespace Canaan
{
    static const Real PI               = 3.14159265358979323846f;
    static const Real TWO_PI           = 6.28318530717958647692f;
    static const Real HALF_PI          = 1.57079632679489661923f;
    static const Real QUARTER_PI       = 0.785398163397448309616f;
    static const Real FLOAT_MAX        = 3.402823466e+10f;
    static const Real DEGREE_TO_RADIAN = PI / 180.0f;
    static const Real RADIAN_TO_DEGREE = 180.0f / PI;

    inline Real RandomUnitization() {
    #if (CN_PLATFORM == CN_PLATFORM_ANDROID)
            return Real(drand48());
    #else
            return (Real)rand() / (Real)RAND_MAX;
    #endif
    }

    inline bool IsNaN(Real val) { return val != val; }

    template<typename T> T Minimum(const T& lVal, const T& rVal) { return lVal < rVal ? lVal : rVal; }
    template<typename T> T Maximum(const T& lVal, const T& rVal) { return lVal < rVal ? rVal : lVal; }
    
}


#endif /* Mathematics_hpp */
