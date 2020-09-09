#ifndef _CN_MATRIX3_
#define _CN_MATRIX3_
#include "Prerequisites.h"
#include "Vector3.h"

/*
The generic form M * V which shows the layout of the matrix
entries is shown below:
<pre>
[ m[0][0]  m[0][1]  m[0][2]]   {x}
| m[1][0]  m[1][1]  m[1][2]| * {y}
[ m[2][0]  m[2][1]  m[2][2]]   {z}
</pre>
*/

namespace Canaan
{
    class CN_EXPORT Mat3
    {
    public:
        static const Mat3 IDENTITY;

        Mat3();
        Mat3(const Mat3 &copy);
        Mat3(Real m00, Real m01, Real m02,
            Real m10, Real m11, Real m12,
            Real m20, Real m21, Real m22);
        ~Mat3();

        void identity();
        void set(Real m00, Real m01, Real m02,
            Real m10, Real m11, Real m12,
            Real m20, Real m21, Real m22);
        void transpose();
        void inverse();

        inline Real* operator [] (size_t iRow){
            cnAssert(iRow < 3);
            return m[iRow];
        }

        inline const Real *operator [] (size_t iRow) const{
            cnAssert(iRow < 3);
            return m[iRow];
        }

        inline Mat3& operator= (const Mat3& rkMatrix)
        {
            memcpy(m, rkMatrix.m, 9 * sizeof(Real));
            return *this;
        }

        inline bool operator== (const Mat3& rkMatrix) const{
            if (
                m[0][0] != rkMatrix.m[0][0] || m[0][1] != rkMatrix.m[0][1] || m[0][2] != rkMatrix.m[0][2] ||
                m[1][0] != rkMatrix.m[1][0] || m[1][1] != rkMatrix.m[1][1] || m[1][2] != rkMatrix.m[1][2] ||
                m[2][0] != rkMatrix.m[2][0] || m[2][1] != rkMatrix.m[2][1] || m[2][2] != rkMatrix.m[2][2])
                return false;
            return true;
        }

        inline bool operator!= (const Mat3& rkMatrix) const{
            return !operator==(rkMatrix);
        }

        inline Mat3 operator+ (const Mat3& rkMatrix) const{
            Mat3 r;

            r.m[0][0] = m[0][0] + rkMatrix.m[0][0];
            r.m[0][1] = m[0][1] + rkMatrix.m[0][1];
            r.m[0][2] = m[0][2] + rkMatrix.m[0][2];

            r.m[1][0] = m[1][0] + rkMatrix.m[1][0];
            r.m[1][1] = m[1][1] + rkMatrix.m[1][1];
            r.m[1][2] = m[1][2] + rkMatrix.m[1][2];

            r.m[2][0] = m[2][0] + rkMatrix.m[2][0];
            r.m[2][1] = m[2][1] + rkMatrix.m[2][1];
            r.m[2][2] = m[2][2] + rkMatrix.m[2][2];

            return r;
        }

        inline Mat3 operator- (const Mat3& rkMatrix) const{
            Mat3 r;
            r.m[0][0] = m[0][0] - rkMatrix.m[0][0];
            r.m[0][1] = m[0][1] - rkMatrix.m[0][1];
            r.m[0][2] = m[0][2] - rkMatrix.m[0][2];

            r.m[1][0] = m[1][0] - rkMatrix.m[1][0];
            r.m[1][1] = m[1][1] - rkMatrix.m[1][1];
            r.m[1][2] = m[1][2] - rkMatrix.m[1][2];

            r.m[2][0] = m[2][0] - rkMatrix.m[2][0];
            r.m[2][1] = m[2][1] - rkMatrix.m[2][1];
            r.m[2][2] = m[2][2] - rkMatrix.m[2][2];

            return r;
        }

        inline Mat3 operator* (const Mat3& m2) const{
            Mat3 r;
            r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0];
            r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1];
            r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2];

            r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0];
            r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1];
            r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2];

            r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0];
            r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1];
            r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2];

            return r;
        }

        inline Mat3 operator* (const Real scalar) const{
            Mat3 r;
            r.m[0][0] = m[0][0] * scalar;
            r.m[0][1] = m[0][1] * scalar;
            r.m[0][2] = m[0][2] * scalar;

            r.m[1][0] = m[1][0] * scalar;
            r.m[1][1] = m[1][1] * scalar;
            r.m[1][2] = m[1][2] * scalar;

            r.m[2][0] = m[2][0] * scalar;
            r.m[2][1] = m[2][1] * scalar;
            r.m[2][2] = m[2][2] * scalar;
            return r;
        }

        inline Vec3 operator* (const Vec3& v) const{
            Vec3 r;
            r.x = (m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z);
            r.y = (m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z);
            r.z = (m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
            return r;
        }

        friend Mat3 operator* (const Real scalar, const Mat3& m){
            Mat3 r;
            r.m[0][0] = m[0][0] * scalar;
            r.m[0][1] = m[0][1] * scalar;
            r.m[0][2] = m[0][2] * scalar;
            
            r.m[1][0] = m[1][0] * scalar;
            r.m[1][1] = m[1][1] * scalar;
            r.m[1][2] = m[1][2] * scalar;
            
            r.m[2][0] = m[2][0] * scalar;
            r.m[2][1] = m[2][1] * scalar;
            r.m[2][2] = m[2][2] * scalar;
            return r;
        }

    private:

        union {
            Real m[3][3];
            Real _m[9];
        };
    };

    /*Mat3 operator* (const Real scalar, const Mat3& m){
        Mat3 r;
        r.m[0][0] = m[0][0] * scalar;
        r.m[0][1] = m[0][1] * scalar;
        r.m[0][2] = m[0][2] * scalar;

        r.m[1][0] = m[1][0] * scalar;
        r.m[1][1] = m[1][1] * scalar;
        r.m[1][2] = m[1][2] * scalar;

        r.m[2][0] = m[2][0] * scalar;
        r.m[2][1] = m[2][1] * scalar;
        r.m[2][2] = m[2][2] * scalar;
        return r;
    }*/
}

#endif
