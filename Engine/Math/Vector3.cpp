#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"

namespace Canaan
{
    const Vec3 Vec3::ZERO            = Vec3();
    const Vec3 Vec3::UNIT_X          = Vec3(1.0f, 0.0f, 0.0f);
    const Vec3 Vec3::UNIT_Y          = Vec3(0.0f, 1.0f, 0.0f);
    const Vec3 Vec3::UNIT_Z          = Vec3(0.0f, 0.0f, 1.0f);
    const Vec3 Vec3::NEGATIVE_UNIT_X = Vec3(-1.0f, 0.0f, 0.0f);
    const Vec3 Vec3::NEGATIVE_UNIT_Y = Vec3(0.0f, -1.0f, 0.0f);
    const Vec3 Vec3::NEGATIVE_UNIT_Z = Vec3(0.0f, 0.0f, -1.0f);
    const Vec3 Vec3::UNIT_SCALE      = Vec3(1.0f);

    Vec3::Vec3()
        : x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {

    }

    Vec3::Vec3(const Vec3 &copy)
        : x(copy.x)
        , y(copy.y)
        , z(copy.z)
    {

    }

    Vec3::Vec3(const Real scaler)
        : x(scaler)
        , y(scaler)
        , z(scaler)
    {

    }

    Vec3::Vec3(Real *xyz)
        : x(xyz[0])
        , y(xyz[1])
        , z(xyz[2])
    {

    }

    Vec3::Vec3(const Real x, const Real y, const Real z)
        : x(x)
        , y(y)
        , z(z)
    {

    }

    Vec3::~Vec3()
    {

    }

    Vec3 Vec3::perpendicular()
    {
        static const Real fSquareZero = Real(1e-06 * 1e-06);
        Vec3 perp;
        perp = this->crossProduct(Vec3::UNIT_X);
        if (perp.squaredLength() < fSquareZero){
            perp = this->crossProduct(Vec3::UNIT_Y);
        }
        perp.normalize();
        return perp;
    }

    Vec3 Vec3::randomDeviat(Real angle, const Vec3 &up)
    {
        Vec3 newUp = up == Vec3::ZERO? this->perpendicular() : up;
        Mat4 mat = Mat4::rotation(Quat(RandomUnitization() * TWO_PI, *this));
        newUp = mat * newUp;
        mat = Mat4::rotation(Quat(angle, newUp));
        return mat * (*this);
    }
}
