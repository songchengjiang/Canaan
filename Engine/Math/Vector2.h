#ifndef _CN_VECTOR2_
#define _CN_VECTOR2_
#include "Prerequisites.h"
#include "Mathematics.h"

namespace Canaan
{
    class CN_EXPORT Vec2
    {
    public:

        // special points
        static const Vec2 ZERO;
        static const Vec2 UNIT_X;
        static const Vec2 UNIT_Y;
        static const Vec2 NEGATIVE_UNIT_X;
        static const Vec2 NEGATIVE_UNIT_Y;
        static const Vec2 UNIT_SCALE;

        Vec2();
        Vec2(const Vec2 &copy);
        Vec2(const Real scaler);
        Vec2(Real *xy);
        Vec2(const Real x, const Real y);
        ~Vec2();

        Real length() const { return sqrt(x * x + y * y); }
        Real squaredLength() const { return x * x + y * y; }
        Real distance(const Vec2& rhs) const { return (*this - rhs).length(); }
        Real squaredDistance(const Vec2& rhs) const{ return (*this - rhs).squaredLength(); }
        Real dotProduct(const Vec2 &vec) const { return x * vec.x + y * vec.y;  }
        Real crossProduct(const Vec2 &vec) const { return x * vec.y - y * vec.x; }

        Real normalize(){
            Real fLength = sqrt(x * x + y * y);

            if (fLength > Real(0.0f)){
                Real fInvLength = 1.0f / fLength;
                x *= fInvLength;
                y *= fInvLength;
            }

            return fLength;
        }

        Vec2 reflect(const Vec2& normal) const{
            return Vec2(*this - (2 * this->dotProduct(normal) * normal));
        }
        
        bool isNaN() const{
            return IsNaN(x) || IsNaN(y);
        }

        bool isZeroLength(void) const{
            Real sqlen = (x * x) + (y * y);
            return (sqlen < (1e-06 * 1e-06));
        }

        inline Real operator [] (const size_t i) const{
            cnAssert(i < 2);
            return *(&x + i);
        }

        inline Real& operator [] (const size_t i){
            cnAssert(i < 2);

            return *(&x + i);
        }

        inline Vec2& operator = (const Vec2& rkVector){
            x = rkVector.x;
            y = rkVector.y;

            return *this;
        }

        inline Vec2& operator = (const Real fScalar){
            x = fScalar;
            y = fScalar;

            return *this;
        }

        inline bool operator == (const Vec2& rkVector) const{
            return (x == rkVector.x && y == rkVector.y);
        }

        inline bool operator != (const Vec2& rkVector) const{
            return (x != rkVector.x || y != rkVector.y);
        }

        // arithmetic operations
        inline Vec2 operator + (const Vec2& rkVector) const{
            return Vec2(x + rkVector.x, y + rkVector.y);
        }

        inline Vec2 operator - (const Vec2& rkVector) const{
            return Vec2(x - rkVector.x, y - rkVector.y);
        }

        inline Vec2 operator * (const Real fScalar) const{
            return Vec2(x * fScalar, y * fScalar);
        }

        inline Vec2 operator * (const Vec2& rhs) const{
            return Vec2(x * rhs.x, y * rhs.y);
        }

        inline Vec2 operator / (const Real fScalar) const{
            cnAssert(fScalar != 0.0);

            Real fInv = 1.0f / fScalar;

            return Vec2(x * fInv, y * fInv);
        }

        inline Vec2 operator / (const Vec2& rhs) const{
            return Vec2(x / rhs.x, y / rhs.y);
        }

        inline const Vec2& operator + () const{
            return *this;
        }

        inline Vec2 operator - () const{
            return Vec2(-x, -y);
        }

        // arithmetic updates
        inline Vec2& operator += (const Vec2& rkVector){
            x += rkVector.x;
            y += rkVector.y;

            return *this;
        }

        inline Vec2& operator += (const Real fScaler){
            x += fScaler;
            y += fScaler;

            return *this;
        }

        inline Vec2& operator -= (const Vec2& rkVector){
            x -= rkVector.x;
            y -= rkVector.y;

            return *this;
        }

        inline Vec2& operator -= (const Real fScaler){
            x -= fScaler;
            y -= fScaler;

            return *this;
        }

        inline Vec2& operator *= (const Real fScalar){
            x *= fScalar;
            y *= fScalar;

            return *this;
        }

        inline Vec2& operator *= (const Vec2& rkVector){
            x *= rkVector.x;
            y *= rkVector.y;

            return *this;
        }

        inline Vec2& operator /= (const Real fScalar){
            cnAssert(fScalar != 0.0);

            Real fInv = 1.0f / fScalar;

            x *= fInv;
            y *= fInv;

            return *this;
        }

        inline Vec2& operator /= (const Vec2& rkVector){
            x /= rkVector.x;
            y /= rkVector.y;

            return *this;
        }

        inline bool operator < (const Vec2& rhs) const{
            if (x < rhs.x && y < rhs.y)
                return true;
            return false;
        }

        inline bool operator >(const Vec2& rhs) const{
            if (rhs.x < x && rhs.y < y)
                return true;
            return false;
        }

        friend Vec2 operator * (const Real fScalar, const Vec2& rkVector){
            return Vec2(fScalar * rkVector.x, fScalar * rkVector.y);
        }
        friend Vec2 operator / (const Real fScalar, const Vec2& rkVector){
            return Vec2(fScalar / rkVector.x, fScalar / rkVector.y);
        }
        friend Vec2 operator + (const Vec2& lhs, const Real rhs){
            return Vec2(lhs.x + rhs, lhs.y + rhs);
        }
        friend Vec2 operator + (const Real lhs, const Vec2& rhs){
            return Vec2(lhs + rhs.x, lhs + rhs.y);
        }
        friend Vec2 operator - (const Vec2& lhs, const Real rhs){
            return Vec2(lhs.x - rhs, lhs.y - rhs);
        }
        friend Vec2 operator - (const Real lhs, const Vec2& rhs){
            return Vec2(lhs - rhs.x, lhs - rhs.y);
        }

        Real x;
        Real y;
    };

    /*Vec2 operator * (const Real fScalar, const Vec2& rkVector){
        return Vec2(fScalar * rkVector.x, fScalar * rkVector.y);
    }

    Vec2 operator / (const Real fScalar, const Vec2& rkVector){
        return Vec2(fScalar / rkVector.x, fScalar / rkVector.y);
    }

    Vec2 operator + (const Vec2& lhs, const Real rhs){
        return Vec2(lhs.x + rhs, lhs.y + rhs);
    }

    Vec2 operator + (const Real lhs, const Vec2& rhs){
        return Vec2(lhs + rhs.x, lhs + rhs.y);
    }

    Vec2 operator - (const Vec2& lhs, const Real rhs){
        return Vec2(lhs.x - rhs, lhs.y - rhs);
    }

    Vec2 operator - (const Real lhs, const Vec2& rhs){
        return Vec2(lhs - rhs.x, lhs - rhs.y);
    }*/

    typedef std::vector<Vec2> Vec2Array;
}

#endif
