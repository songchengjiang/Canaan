#include "Quaternion.h"
#include "Matrix3.h"

namespace Canaan
{
    const Quat Quat::ZERO = Quat(0.0f, 0.0f, 0.0f, 0.0f);
    const Quat Quat::IDENTITY = Quat();
    static const Real msEpsilon = 1e-03f;

    Quat::Quat()
        : w(1.0f)
        , x(0.0f)
        , y(0.0f)
        , z(0.0f)
    {

    }

    Quat::Quat(const Real w, const Real x, const Real y, const Real z)
        : w(w)
        , x(x)
        , y(y)
        , z(z)
    {

    }

    Quat::Quat(const Real angle, const Vec3 &axes)
    {
        this->fromAngleAxis(angle, axes);
    }

    Quat::Quat(const Quat &copy)
        : w(copy.w)
        , x(copy.x)
        , y(copy.y)
        , z(copy.z)
    {

    }

    Quat::Quat(const Mat3 &rotMat)
    {
        this->fromMat3(rotMat);
    }

    Quat::~Quat()
    {

    }

    void Quat::set(const Real angle, const Vec3 &axes)
    {
        this->fromAngleAxis(angle, axes);
    }

    void Quat::set(const Mat3 &rotMat)
    {
        this->fromMat3(rotMat);
    }

    Real Quat::dot(const Quat &rkQ) const
    {
        return w * rkQ.w + x * rkQ.x + y * rkQ.y + z * rkQ.z;
    }

    Real Quat::normalize()
    {
        Real len = normLength();
        Real factor = 1.0f / sqrt(len);
        *this = *this * factor;
        return len;
    }

    void Quat::inverse()
    {
        Real fNorm = normLength();
        if (fNorm > 0.0)
        {
            Real fInvNorm = 1.0f / fNorm;
            w *= fInvNorm;
            x *= -fInvNorm;
            y *= -fInvNorm;
            z *= -fInvNorm;
        }
    }

    void Quat::unitInverse()
    {
        x = -x;
        y = -y;
        z = -z;
    }

    Real Quat::roll(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            // roll = atan2(localx.y, localx.x)
            // pick parts of xAxis() implementation that we need
            //			Real fTx  = 2.0*x;
            Real fTy = 2.0f * y;
            Real fTz = 2.0f * z;
            Real fTwz = fTz * w;
            Real fTxy = fTy * x;
            Real fTyy = fTy * y;
            Real fTzz = fTz * z;

            // Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

            return atan2(fTxy + fTwz, 1.0f - (fTyy + fTzz));

        }
        else
        {
            return atan2(2 * (x * y + w * z), w * w + x * x - y * y - z * z);
        }
    }

    Real Quat::pitch(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            // pitch = atan2(localy.z, localy.y)
            // pick parts of yAxis() implementation that we need
            Real fTx = 2.0f * x;
            //			Real fTy  = 2.0f*y;
            Real fTz = 2.0f * z;
            Real fTwx = fTx * w;
            Real fTxx = fTx * x;
            Real fTyz = fTz * y;
            Real fTzz = fTz * z;

            // Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
            return atan2(fTyz + fTwx, 1.0f - (fTxx + fTzz));
        }
        else
        {
            // internal version
            return atan2(2 * (y * z + w * x), w * w - x * x - y * y + z * z);
        }
    }

    Real Quat::yaw(bool reprojectAxis) const
    {
        if (reprojectAxis)
        {
            // yaw = atan2(localz.x, localz.z)
            // pick parts of zAxis() implementation that we need
            Real fTx = 2.0f * x;
            Real fTy = 2.0f * y;
            Real fTz = 2.0f * z;
            Real fTwy = fTy * w;
            Real fTxx = fTx * x;
            Real fTxz = fTz * x;
            Real fTyy = fTy * y;

            // Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

            return atan2(fTxz + fTwy, 1.0f - (fTxx + fTyy));

        }
        else
        {
            // internal version
            return sin(-2 * (x * z - w * y));
        }
    }

    Quat Quat::slerp(Real fT, const Quat& rkP, const Quat& rkQ, bool shortestPath /*= false*/)
    {
        Real fCos = rkP.dot(rkQ);
        Quat rkT;

        // Do we need to invert rotation?
        if (fCos < 0.0f && shortestPath)
        {
            fCos = -fCos;
            rkT = -rkQ;
        }
        else
        {
            rkT = rkQ;
        }

        if (abs(fCos) < 1 - msEpsilon)
        {
            // Standard case (slerp)
            Real fSin = sqrt(1 - fCos * fCos);
            Real fAngle = atan2(fSin, fCos);
            Real fInvSin = 1.0f / fSin;
            Real fCoeff0 = sin((1.0f - fT) * fAngle) * fInvSin;
            Real fCoeff1 = sin(fT * fAngle) * fInvSin;
            return fCoeff0 * rkP + fCoeff1 * rkT;
        }
        else
        {
            // There are two situations:
            // 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
            //    interpolation safely.
            // 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
            //    are an infinite number of possibilities interpolation. but we haven't
            //    have method to fix this case, so just use linear interpolation here.
            Quat t = (1.0f - fT) * rkP + fT * rkT;
            // taking the complement requires renormalisation
            t.normalize();
            return t;
        }
    }

    Quat Quat::nlerp(Real fT, const Quat& rkP, const Quat& rkQ, bool shortestPath /*= false*/)
    {
        Quat result;
        Real fCos = rkP.dot(rkQ);
        if (fCos < 0.0f && shortestPath)
        {
            result = rkP + fT * ((-rkQ) - rkP);
        }
        else
        {
            result = rkP + fT * (rkQ - rkP);
        }
        result.normalize();
        return result;
    }

    Quat Quat::squad(Real fT, const Quat& rkP, const Quat& rkA, const Quat& rkB, const Quat& rkQ, bool shortestPath /*= false*/)
    {
        Real fSlerpT = 2.0f*fT*(1.0f - fT);
        Quat kSlerpP = slerp(fT, rkP, rkQ, shortestPath);
        Quat kSlerpQ = slerp(fT, rkA, rkB);
        return slerp(fSlerpT, kSlerpP, kSlerpQ);
    }

    void Quat::fromAngleAxis(const Real angle, const Vec3 &axes)
    {
        Real fHalfAngle(0.5f*angle);
        Real fSin = sin(fHalfAngle);
        Vec3 normal(axes);
        normal.normalize();
        w = cos(fHalfAngle);
        x = fSin * normal.x;
        y = fSin * normal.y;
        z = fSin * normal.z;
    }

    void Quat::fromMat3(const Mat3 &mat)
    {
        // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
        // article "Quaternion Calculus and Fast Animation".

        Real fTrace = mat[0][0] + mat[1][1] + mat[2][2];
        Real fRoot;

        if (fTrace > 0.0)
        {
            // |w| > 1/2, may as well choose w > 1/2
            fRoot = sqrt(fTrace + 1.0f);  // 2w
            w = 0.5f*fRoot;
            fRoot = 0.5f / fRoot;  // 1/(4w)
            x = (mat[2][1] - mat[1][2])*fRoot;
            y = (mat[0][2] - mat[2][0])*fRoot;
            z = (mat[1][0] - mat[0][1])*fRoot;
        }
        else
        {
            // |w| <= 1/2
            static size_t s_iNext[3] = { 1, 2, 0 };
            size_t i = 0;
            if (mat[1][1] > mat[0][0])
                i = 1;
            if (mat[2][2] > mat[i][i])
                i = 2;
            size_t j = s_iNext[i];
            size_t k = s_iNext[j];

            fRoot = sqrt(mat[i][i] - mat[j][j] - mat[k][k] + 1.0f);
            Real* apkQuat[3] = { &x, &y, &z };
            *apkQuat[i] = 0.5f*fRoot;
            fRoot = 0.5f / fRoot;
            w = (mat[k][j] - mat[j][k])*fRoot;
            *apkQuat[j] = (mat[j][i] + mat[i][j])*fRoot;
            *apkQuat[k] = (mat[k][i] + mat[i][k])*fRoot;
        }
    }
}
