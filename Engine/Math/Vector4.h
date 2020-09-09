#ifndef _CN_VECTOR4_
#define _CN_VECTOR4_
#include "Prerequisites.h"
#include "Mathematics.h"

namespace Canaan
{
    class CN_EXPORT Vec4
    {
    public:

        // special points
        static const Vec4 ZERO;
        static const Vec4 UNIT_SCALE;

        Vec4();
        Vec4(const Vec4 &copy);
        Vec4(const Real scaler);
        Vec4(Real *xyzw);
        Vec4(const Real x, const Real y, const Real z, const Real w);
        ~Vec4();

        bool isNaN() const{
            return IsNaN(x) || IsNaN(y) || IsNaN(z);
        }

        bool isZeroLength(void) const{
            Real sqlen = (x * x) + (y * y) + (z * z) + (w * w);
            return (sqlen < (1e-06 * 1e-06));
        }

        inline Real operator [] (const size_t i) const{
            cnAssert(i < 4);
            return *(&x + i);
        }

        inline Real& operator [] (const size_t i){
            cnAssert(i < 4);

            return *(&x + i);
        }

        inline Vec4& operator = (const Vec4& rkVector){
            x = rkVector.x;
            y = rkVector.y;
            z = rkVector.z;
            w = rkVector.w;

            return *this;
        }

        inline Vec4& operator = (const Real fScalar){
            x = fScalar;
            y = fScalar;
            z = fScalar;
            w = fScalar;

            return *this;
        }

        inline bool operator == (const Vec4& rkVector) const{
            return (x == rkVector.x && y == rkVector.y && z == rkVector.z && w == rkVector.w);
        }

        inline bool operator != (const Vec4& rkVector) const{
            return (x != rkVector.x || y != rkVector.y || z != rkVector.z || w != rkVector.w);
        }

        // arithmetic operations
        inline Vec4 operator + (const Vec4& rkVector) const{
            return Vec4(x + rkVector.x, y + rkVector.y, z + rkVector.z, w + rkVector.w);
        }

        inline Vec4 operator - (const Vec4& rkVector) const{
            return Vec4(x - rkVector.x, y - rkVector.y, z - rkVector.z, w - rkVector.w);
        }

        inline Vec4 operator * (const Real fScalar) const{
            return Vec4(x * fScalar, y * fScalar, z * fScalar, w * fScalar);
        }

        inline Vec4 operator * (const Vec4& rhs) const{
            return Vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }

        inline Vec4 operator / (const Real fScalar) const{
            cnAssert(fScalar != 0.0);

            Real fInv = 1.0f / fScalar;

            return Vec4(x * fInv, y * fInv, z * fInv, w * fInv);
        }

        inline Vec4 operator / (const Vec4& rhs) const{
            return Vec4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
        }

        inline const Vec4& operator + () const{
            return *this;
        }

        inline Vec4 operator - () const{
            return Vec4(-x, -y, -z, -w);
        }

        // arithmetic updates
        inline Vec4& operator += (const Vec4& rkVector){
            x += rkVector.x;
            y += rkVector.y;
            z += rkVector.z;
            w += rkVector.w;

            return *this;
        }

        inline Vec4& operator += (const Real fScaler){
            x += fScaler;
            y += fScaler;
            z += fScaler;
            w += fScaler;

            return *this;
        }

        inline Vec4& operator -= (const Vec4& rkVector){
            x -= rkVector.x;
            y -= rkVector.y;
            z -= rkVector.z;
            w -= rkVector.w;

            return *this;
        }

        inline Vec4& operator -= (const Real fScaler){
            x -= fScaler;
            y -= fScaler;
            z -= fScaler;
            w -= fScaler;

            return *this;
        }

        inline Vec4& operator *= (const Real fScalar){
            x *= fScalar;
            y *= fScalar;
            z *= fScalar;
            w *= fScalar;

            return *this;
        }

        inline Vec4& operator *= (const Vec4& rkVector){
            x *= rkVector.x;
            y *= rkVector.y;
            z *= rkVector.z;
            w *= rkVector.z;

            return *this;
        }

        inline Vec4& operator /= (const Real fScalar){
            cnAssert(fScalar != 0.0);

            Real fInv = 1.0f / fScalar;

            x *= fInv;
            y *= fInv;
            z *= fInv;
            w *= fInv;

            return *this;
        }

        inline Vec4& operator /= (const Vec4& rkVector){
            x /= rkVector.x;
            y /= rkVector.y;
            z /= rkVector.z;
            w /= rkVector.w;

            return *this;
        }

        inline bool operator < (const Vec4& rhs) const{
            if (x < rhs.x && y < rhs.y  && z < rhs.z  && w < rhs.w)
                return true;
            return false;
        }

        inline bool operator >(const Vec4& rhs) const{
            if (rhs.x < x && rhs.y < y && rhs.z < z && rhs.w < w)
                return true;
            return false;
        }

        friend Vec4 operator * (const Real fScalar, const Vec4& rkVector){
            return Vec4(fScalar * rkVector.x, fScalar * rkVector.y, fScalar * rkVector.z, fScalar * rkVector.w);
        }
        friend Vec4 operator / (const Real fScalar, const Vec4& rkVector){
            return Vec4(fScalar / rkVector.x, fScalar / rkVector.y, fScalar / rkVector.z, fScalar / rkVector.w);
        }
        friend Vec4 operator + (const Vec4& lhs, const Real rhs){
            return Vec4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
        }
        friend Vec4 operator + (const Real lhs, const Vec4& rhs){
            return Vec4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
        }
        friend Vec4 operator - (const Vec4& lhs, const Real rhs){
            return Vec4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
        }
        friend Vec4 operator - (const Real lhs, const Vec4& rhs){
            return Vec4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
        }

        Real x;
        Real y;
        Real z;
        Real w;
    };

    /*Vec4 operator * (const Real fScalar, const Vec4& rkVector){
        return Vec4(fScalar * rkVector.x, fScalar * rkVector.y, fScalar * rkVector.z, fScalar * rkVector.w);
    }

    Vec4 operator / (const Real fScalar, const Vec4& rkVector){
        return Vec4(fScalar / rkVector.x, fScalar / rkVector.y, fScalar / rkVector.z, fScalar / rkVector.w);
    }

    Vec4 operator + (const Vec4& lhs, const Real rhs){
        return Vec4(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
    }

    Vec4 operator + (const Real lhs, const Vec4& rhs){
        return Vec4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
    }

    Vec4 operator - (const Vec4& lhs, const Real rhs){
        return Vec4(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
    }

    Vec4 operator - (const Real lhs, const Vec4& rhs){
        return Vec4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
    }*/

    typedef std::vector<Vec4> Vec4Array;
}

#endif
