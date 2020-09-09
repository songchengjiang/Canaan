#include "Vector2.h"

namespace Canaan
{
    const Vec2 Vec2::ZERO            = Vec2();
    const Vec2 Vec2::UNIT_X          = Vec2(1.0f, 0.0f);
    const Vec2 Vec2::UNIT_Y          = Vec2(0.0f, 1.0f);
    const Vec2 Vec2::NEGATIVE_UNIT_X = Vec2(-1.0f, 0.0f);
    const Vec2 Vec2::NEGATIVE_UNIT_Y = Vec2(0.0f, -1.0f);
    const Vec2 Vec2::UNIT_SCALE      = Vec2(1.0f);

    Vec2::Vec2()
        : x(0.0f)
        , y(0.0f)
    {

    }

    Vec2::Vec2(const Vec2 &copy)
        : x(copy.x)
        , y(copy.y)
    {

    }

    Vec2::Vec2(const Real scaler)
        : x(scaler)
        , y(scaler)
    {

    }

    Vec2::Vec2(Real *xy)
        : x(xy[0])
        , y(xy[1])
    {

    }

    Vec2::Vec2(const Real x, const Real y)
        : x(x)
        , y(y)
    {

    }

    Vec2::~Vec2()
    {

    }
}
