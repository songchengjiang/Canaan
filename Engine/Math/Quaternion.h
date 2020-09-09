#ifndef _CN_QUATERNION_
#define _CN_QUATERNION_
#include "Prerequisites.h"
#include "Vector3.h"

namespace Canaan
{
    class Mat3;
    class CN_EXPORT Quat
    {
    public:

        static const Quat ZERO;
        static const Quat IDENTITY;

        Quat();
        Quat(const Quat &copy);
        Quat(const Mat3 &rotMat);
        Quat(const Real w, const Real x, const Real y, const Real z);
        Quat(const Real angle, const Vec3 &axes);
        ~Quat();

        void set(const Mat3 &rotMat);
        void set(const Real angle, const Vec3 &axes);
        Real dot(const Quat &rkQ) const;
        Real normalize();
        void inverse();
        void unitInverse();
        Real roll(bool reprojectAxis = true) const;
        Real pitch(bool reprojectAxis = true) const;
        Real yaw(bool reprojectAxis = true) const;
        Real normLength() const { return w * w + x * x + y * y + z * z; }

        bool isNaN() const
        {
            return IsNaN(x) || IsNaN(y) || IsNaN(z) || IsNaN(w);
        }

        static Quat slerp(Real fT, const Quat& rkP, const Quat& rkQ, bool shortestPath = false);
        //nlerp is faster than Slerp.
        static Quat nlerp(Real fT, const Quat& rkP, const Quat& rkQ, bool shortestPath = false);
        static Quat squad(Real fT, const Quat& rkP,
            const Quat& rkA, const Quat& rkB,
            const Quat& rkQ, bool shortestPath = false);

        inline Real operator [] (const size_t i) const{
            cnAssert(i < 4);

            return *(&w + i);
        }

        /// Array accessor operator
        inline Real& operator [] (const size_t i){
            cnAssert(i < 4);

            return *(&w + i);
        }

        inline Quat& operator= (const Quat& rkQ){
            w = rkQ.w;
            x = rkQ.x;
            y = rkQ.y;
            z = rkQ.z;
            return *this;
        }

        Quat operator+ (const Quat& rkQ) const{
            return Quat(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z);
        }

        Quat operator- (const Quat& rkQ) const{
            return Quat(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z);
        }

        Quat operator* (const Quat& rkQ) const{
            // NOTE:  Multiplication is not generally commutative, so in most
            // cases p*q != q*p.
            return Quat
                (
                w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
                w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
                w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
                w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
                );
        }

        Quat& operator*= (const Quat& rkQ){
            // NOTE:  Multiplication is not generally commutative, so in most
            // cases p*q != q*p.
            Real ww = w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z;
            Real xx = w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y;
            Real yy = w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z;
            Real zz = w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x;
            w = ww; x = xx; y = yy; z = zz;

            return *this;
        }

        Quat operator* (Real fScalar) const{
            return Quat(fScalar * w, fScalar * x, fScalar * y, fScalar * z);
        }

        Vec3 operator* (const Vec3& v) const{
            // nVidia SDK implementation
            Vec3 uv, uuv;
            Vec3 qvec(x, y, z);
            uv = qvec.crossProduct(v);
            uuv = qvec.crossProduct(uv);
            uv *= (2.0f * w);
            uuv *= 2.0f;

            return v + uv + uuv;
        }

        Quat operator- () const{
            return Quat(-w, -x, -y, -z);
        }

        inline bool operator== (const Quat& rhs) const{
            return (rhs.x == x) && (rhs.y == y) &&
                (rhs.z == z) && (rhs.w == w);
        }

        inline bool operator!= (const Quat& rhs) const{
            return !operator==(rhs);
        }

        friend Quat operator * (const Real fScalar, const Quat& rkQ){
            return Quat(fScalar * rkQ.w, fScalar * rkQ.y, fScalar * rkQ.z, fScalar * rkQ.z);
        }
        friend Vec3 operator * (const Vec3& v, const Quat& rkQ){
            // nVidia SDK implementation
            Vec3 uv, uuv;
            Vec3 qvec(rkQ.x, rkQ.y, rkQ.z);
            uv = qvec.crossProduct(v);
            uuv = qvec.crossProduct(uv);
            uv *= (2.0f * rkQ.w);
            uuv *= 2.0f;
            
            return v + uv + uuv;
        }
        
        Real w;
        Real x;
        Real y;
        Real z;

    private:

        void fromAngleAxis(const Real angle, const Vec3 &axes);
        void fromMat3(const Mat3 &mat);
    };

    /*Quat operator * (const Real fScalar, const Quat& rkQ){
        return Quat(fScalar * rkQ.w, fScalar * rkQ.y, fScalar * rkQ.z, fScalar * rkQ.z);
    }

    Vec3 operator * (const Vec3& v, const Quat& rkQ){
        // nVidia SDK implementation
        Vec3 uv, uuv;
        Vec3 qvec(rkQ.x, rkQ.y, rkQ.z);
        uv = qvec.crossProduct(v);
        uuv = qvec.crossProduct(uv);
        uv *= (2.0f * rkQ.w);
        uuv *= 2.0f;

        return v + uv + uuv;
    }*/
}
#endif
