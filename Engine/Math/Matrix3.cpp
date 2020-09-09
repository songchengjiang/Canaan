#include "Matrix3.h"

namespace Canaan
{
    const Mat3 Mat3::IDENTITY = Mat3(1.0f, 0.0f, 0.0f
                                         , 0.0f, 1.0f, 0.0f
                                         , 0.0f, 0.0f, 1.0f);

    Mat3::Mat3()
    {

    }

    Mat3::Mat3(const Mat3 &copy)
    {

    }

    Mat3::Mat3(Real m00, Real m01, Real m02
        , Real m10, Real m11, Real m12
        , Real m20, Real m21, Real m22)
    {
        set(m00, m01, m02
            , m10, m11, m12
            , m20, m21, m22);
    }

    Mat3::~Mat3()
    {

    }

    void Mat3::identity()
    {
        m[0][0] = 1.0f;
        m[0][1] = 0.0f;
        m[0][2] = 0.0f;
        m[1][0] = 0.0f;
        m[1][1] = 1.0f;
        m[1][2] = 0.0f;
        m[2][0] = 0.0f;
        m[2][1] = 0.0f;
        m[2][2] = 1.0f;
    }

    void Mat3::set(Real m00, Real m01, Real m02
        , Real m10, Real m11, Real m12
        , Real m20, Real m21, Real m22)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
    }

    void Mat3::transpose()
    {
        set(m[0][0], m[1][0], m[2][0],
            m[0][1], m[1][1], m[2][1],
            m[0][2], m[1][2], m[2][2]);
    }

    void Mat3::inverse()
    {
        // Invert a 3x3 using cofactors.  This is about 8 times faster than
        // the Numerical Recipes code which uses Gaussian elimination.
        Real d00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
        Real d01 = m[0][2] * m[2][1] - m[0][1] * m[2][2];
        Real d02 = m[0][1] * m[1][2] - m[0][2] * m[1][1];
        Real d10 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
        Real d11 = m[0][0] * m[2][2] - m[0][2] * m[2][0];
        Real d12 = m[0][2] * m[1][0] - m[0][0] * m[1][2];
        Real d20 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
        Real d21 = m[0][1] * m[2][0] - m[0][0] * m[2][1];
        Real d22 = m[0][0] * m[1][1] - m[0][1] * m[1][0];

        Real fDet = m[0][0] * d00 + m[0][1] * d10 + m[0][2] * d20;

        Real fInvDet = 1.0f / fDet;
        set(d00 * fInvDet, d01 * fInvDet, d02 * fInvDet
            , d10 * fInvDet, d11 * fInvDet, d12 * fInvDet
            , d20 * fInvDet, d21 * fInvDet, d22 * fInvDet);
    }
}
