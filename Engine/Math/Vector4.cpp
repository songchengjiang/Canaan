#include "Vector4.h"

namespace Canaan
{
    const Vec4 Vec4::ZERO = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    const Vec4 Vec4::UNIT_SCALE = Vec4(1.0f);

    Vec4::Vec4()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
        , w(0.0f)
    {

    }

    Vec4::Vec4(const Vec4 &copy)
        : x(copy.x)
        , y(copy.y)
        , z(copy.z)
        , w(copy.w)
    {

    }

    Vec4::Vec4(const Real scaler)
        : x(scaler)
        , y(scaler)
        , z(scaler)
        , w(scaler)
    {

    }

    Vec4::Vec4(Real *xyzw)
        : x(xyzw[0])
        , y(xyzw[1])
        , z(xyzw[2])
        , w(xyzw[3])
    {

    }

    Vec4::Vec4(const Real x, const Real y, const Real z, const Real w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {

    }

    Vec4::~Vec4()
    {

    }
}
