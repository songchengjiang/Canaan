#ifndef _CN_TRANSFORM_
#define _CN_TRANSFORM_
#include "Prerequisites.h"
#include "Math/Matrix4.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace Canaan
{
    class SceneObject;
    class CN_EXPORT Transform
    {
    public:
        
        Transform();
        ~Transform();
        
        const Mat4& getLocalMatrix();
        const Mat4& getWorldMatrix();
        
        void setLocalPosition(const Vec3& pos);
        const Vec3& getLocalPosition() const;
        
        void setWorldPosition(Vec3 pos);
        Vec3 getWorldPosition() const;
        
        void setLocalOrientation(const Quat& rot);
        const Quat& getLocalOrientation() const;
        
        void setWorldOrientation(Quat rot);
        Quat getWorldOrientation() const;
        
        void setLocalScale(const Vec3& scl);
        const Vec3& getLocalScale() const;
        
        void setWorldScale(Vec3 scl);
        Vec3 getWorldScale() const;
        
    private:
        
        void onNotifyTransformChanged();
        
    private:
        
        Mat4 m_localMat;
        Mat4 m_worldMat;
        Vec3 m_localPosition;
        Vec3 m_localScale       = Vec3::UNIT_SCALE;
        Quat m_localOrientation = Quat::IDENTITY;
        
        friend class SceneObject;
        SceneObject* m_attachedSO = nullptr;
        
        int m_dirtyFlag = 0;
    };
}

#endif 
