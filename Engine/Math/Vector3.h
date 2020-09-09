#ifndef _CN_VECTOR3_
#define _CN_VECTOR3_
#include "Prerequisites.h"
#include "Mathematics.h"

namespace Canaan
{
    class CN_EXPORT Vec3
    {
    public:

        // special points
        static const Vec3 ZERO;
        static const Vec3 UNIT_X;
        static const Vec3 UNIT_Y;
        static const Vec3 UNIT_Z;
        static const Vec3 NEGATIVE_UNIT_X;
        static const Vec3 NEGATIVE_UNIT_Y;
        static const Vec3 NEGATIVE_UNIT_Z;
        static const Vec3 UNIT_SCALE;

        Vec3();
        Vec3(const Vec3 &copy);
        Vec3(const Real scaler);
        Vec3(Real *xyz);
        Vec3(const Real x, const Real y, const Real z);
        ~Vec3();

        Real length() const { return sqrt(x * x + y * y + z * z); }
        Real squaredLength() const { return x * x + y * y + z * z; }
        Real distance(const Vec3& rhs) const { return (*this - rhs).length(); }
        Real squaredDistance(const Vec3& rhs) const{ return (*this - rhs).squaredLength(); }
        Real dotProduct(const Vec3 &vec) const { return x * vec.x + y * vec.y + z * vec.z; }
        Vec3 crossProduct(const Vec3 &vec) const {
            return Vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
        }
        
        Vec3 perpendicular();
        Vec3 randomDeviat(Real angle, const Vec3 &up = Vec3::ZERO);

        Real normalize(){
            Real fLength = sqrt(x * x + y * y + z * z);

            if (fLength > Real(0.0f))
            {
                Real fInvLength = 1.0f / fLength;
                x *= fInvLength;
                y *= fInvLength;
                z *= fInvLength;
            }

            return fLength;
        }

        Vec3 reflect(const Vec3& normal) const{
            return Vec3(*this - (2 * this->dotProduct(normal) * normal));
        }

        bool isNaN() const{
            return IsNaN(x) || IsNaN(y) || IsNaN(z);
        }

        bool isZeroLength(void) const{
            Real sqlen = (x * x) + (y * y) + (z * z);
            return (sqlen < (1e-06 * 1e-06));
        }

        inline Real operator [] (const size_t i) const{
            cnAssert(i < 3);
            return *(&x + i);
        }

        inline Real& operator [] (const size_t i){
            cnAssert(i < 3);

            return *(&x + i);
        }

        inline Vec3& operator = (const Vec3& rkVector){
            x = rkVector.x;
            y = rkVector.y;
            z = rkVector.z;

            return *this;
        }

        inline Vec3& operator = (const Real fScalar){
            x = fScalar;
            y = fScalar;
            z = fScalar;

            return *this;
        }

        inline bool operator == (const Vec3& rkVector) const{
            return (x == rkVector.x && y == rkVector.y && z == rkVector.z);
        }

        inline bool operator != (const Vec3& rkVector) const{
            return (x != rkVector.x || y != rkVector.y || z != rkVector.z);
        }

        // arithmetic operations
        inline Vec3 operator + (const Vec3& rkVector) const{
            return Vec3(x + rkVector.x, y + rkVector.y, z + rkVector.z);
        }

        inline Vec3 operator - (const Vec3& rkVector) const{
            return Vec3(x - rkVector.x, y - rkVector.y, z - rkVector.z);
        }

        inline Vec3 operator * (const Real fScalar) const{
            return Vec3(x * fScalar, y * fScalar, z * fScalar);
        }

        inline Vec3 operator * (const Vec3& rhs) const{
            return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
        }

        inline Vec3 operator / (const Real fScalar) const{
            cnAssert(fScalar != 0.0);

            Real fInv = 1.0f / fScalar;

            return Vec3(x * fInv, y * fInv, z * fInv);
        }

        inline Vec3 operator / (const Vec3& rhs) const{
            return Vec3(x / rhs.x, y / rhs.y, z / rhs.z);
        }

        inline const Vec3& operator + () const{
            return *this;
        }

        inline Vec3 operator - () const{
            return Vec3(-x, -y, -z);
        }

        // arithmetic updates
        inline Vec3& operator += (const Vec3& rkVector){
            x += rkVector.x;
            y += rkVector.y;
            z += rkVector.z;

            return *this;
        }

        inline Vec3& operator += (const Real fScaler){
            x += fScaler;
            y += fScaler;
            z += fScaler;

            return *this;
        }

        inline Vec3& operator -= (const Vec3& rkVector){
            x -= rkVector.x;
            y -= rkVector.y;
            z -= rkVector.z;

            return *this;
        }

        inline Vec3& operator -= (const Real fScaler){
            x -= fScaler;
            y -= fScaler;
            z -= fScaler;

            return *this;
        }

        inline Vec3& operator *= (const Real fScalar){
            x *= fScalar;
            y *= fScalar;
            z *= fScalar;

            return *this;
        }

        inline Vec3& operator *= (const Vec3& rkVector){
            x *= rkVector.x;
            y *= rkVector.y;
            z *= rkVector.z;

            return *this;
        }

        inline Vec3& operator /= (const Real fScalar){
            cnAssert(fScalar != 0.0);

            Real fInv = 1.0f / fScalar;

            x *= fInv;
            y *= fInv;
            z *= fInv;

            return *this;
        }

        inline Vec3& operator /= (const Vec3& rkVector){
            x /= rkVector.x;
            y /= rkVector.y;
            z /= rkVector.z;

            return *this;
        }

        inline bool operator < (const Vec3& rhs) const{
            if (x < rhs.x && y < rhs.y  && z < rhs.z)
                return true;
            return false;
        }

        inline bool operator >(const Vec3& rhs) const{
            if (rhs.x < x && rhs.y < y && rhs.z < z)
                return true;
            return false;
        }

        inline bool operator <= (const Vec3& rhs) const {
            if (x <= rhs.x && y <= rhs.y  && z <= rhs.z)
                return true;
            return false;
        }

        inline bool operator >=(const Vec3& rhs) const {
            if (rhs.x <= x && rhs.y <= y && rhs.z <= z)
                return true;
            return false;
        }

        friend Vec3 operator * (const Real fScalar, const Vec3& rkVector){
            return Vec3(fScalar * rkVector.x, fScalar * rkVector.y, fScalar * rkVector.z);
        }
        friend Vec3 operator / (const Real fScalar, const Vec3& rkVector){
            return Vec3(fScalar / rkVector.x, fScalar / rkVector.y, fScalar / rkVector.z);
        }
        friend Vec3 operator + (const Vec3& lhs, const Real rhs){
            return Vec3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
        }
        friend Vec3 operator + (const Real lhs, const Vec3& rhs){
            return Vec3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
        }
        friend Vec3 operator - (const Vec3& lhs, const Real rhs){
            return Vec3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
        }
        friend Vec3 operator - (const Real lhs, const Vec3& rhs){
            return Vec3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
        }

        Real x;
        Real y;
        Real z;
    };

    /*Vec3 operator * (const Real fScalar, const Vec3& rkVector){
        return Vec3(fScalar * rkVector.x, fScalar * rkVector.y, fScalar * rkVector.z);
    }

    Vec3 operator / (const Real fScalar, const Vec3& rkVector){
        return Vec3(fScalar / rkVector.x, fScalar / rkVector.y, fScalar / rkVector.z);
    }

    Vec3 operator + (const Vec3& lhs, const Real rhs){
        return Vec3(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
    }

    Vec3 operator + (const Real lhs, const Vec3& rhs){
        return Vec3(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
    }

    Vec3 operator - (const Vec3& lhs, const Real rhs){
        return Vec3(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
    }

    Vec3 operator - (const Real lhs, const Vec3& rhs){
        return Vec3(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
    }*/

    typedef std::vector<Vec3> Vec3Array;
}

#endif
