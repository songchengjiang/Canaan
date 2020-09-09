//
//  Transform.cpp
//  Engine
//
//  Created by 蒋颂晟 on 2020/9/9.
//  Copyright © 2020 蒋颂晟. All rights reserved.
//

#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"

namespace Canaan
{
    static const int TRANSFORM_LOCAL_MATRIX_DIRTY_FLAG = 1;
    static const int TRANSFORM_WORLD_MATRIX_DIRTY_FLAG = 1 << 1;
    static const int TRANSFORM_ALL_FLAG = TRANSFORM_LOCAL_MATRIX_DIRTY_FLAG | TRANSFORM_WORLD_MATRIX_DIRTY_FLAG;

    Transform::Transform()
    : m_dirtyFlag(TRANSFORM_ALL_FLAG)
    {
    }

    Transform::~Transform()
    {
        
    }

    const Mat4& Transform::getLocalMatrix()
    {
        if (m_dirtyFlag & TRANSFORM_LOCAL_MATRIX_DIRTY_FLAG)
        {
            m_localMat = Mat4::transform(m_localPosition, m_localScale, m_localOrientation);
        }
        return m_localMat;
    }

    const Mat4& Transform::getWorldMatrix()
    {
        if (m_dirtyFlag & TRANSFORM_WORLD_MATRIX_DIRTY_FLAG)
        {
            m_worldMat = m_attachedSO->getParent() ? m_attachedSO->getParent()->getTransform()->getWorldMatrix() * getLocalMatrix(): getLocalMatrix();
        }
        return m_worldMat;
    }
    
    void Transform::setLocalPosition(const Vec3& pos)
    {
        m_localPosition = pos;
        m_dirtyFlag |= TRANSFORM_LOCAL_MATRIX_DIRTY_FLAG;
        m_dirtyFlag |= TRANSFORM_WORLD_MATRIX_DIRTY_FLAG;
        onNotifyTransformChanged();
    }

    const Vec3& Transform::getLocalPosition() const
    {
        return m_localPosition;
    }
    
    void Transform::setWorldPosition(Vec3 pos)
    {
        if (m_attachedSO->getParent())
        {
            Mat4 worldMat = m_attachedSO->getParent()->getTransform()->getWorldMatrix();
            worldMat.inverse();
            setLocalPosition(worldMat * pos);
        }
        else
        {
            setLocalPosition(pos);
        }
    }

    Vec3 Transform::getWorldPosition() const
    {
        if (m_attachedSO->getParent())
        {
            return m_attachedSO->getParent()->getTransform()->getWorldMatrix() * m_localPosition;
        }
        else
        {
            return m_localPosition;
        }
    }
    
    void Transform::setLocalOrientation(const Quat& rot)
    {
        m_localOrientation = rot;
        m_dirtyFlag |= TRANSFORM_LOCAL_MATRIX_DIRTY_FLAG;
        m_dirtyFlag |= TRANSFORM_WORLD_MATRIX_DIRTY_FLAG;
        onNotifyTransformChanged();
    }

    const Quat& Transform::getLocalOrientation() const
    {
        return m_localOrientation;
    }
    
    void Transform::setWorldOrientation(Quat rot)
    {
        if (m_attachedSO->getParent())
        {
            Quat worldRot = m_attachedSO->getParent()->getTransform()->getWorldOrientation();
            worldRot.inverse();
            setLocalOrientation(worldRot * rot);
        }
        else
        {
            setLocalOrientation(rot);
        }
    }

    Quat Transform::getWorldOrientation() const
    {
        if (m_attachedSO->getParent())
        {
            return m_attachedSO->getParent()->getTransform()->getWorldOrientation() * m_localOrientation;
        }
        else
        {
            return m_localOrientation;
        }
    }
    
    void Transform::setLocalScale(const Vec3& scl)
    {
        m_localScale = scl;
        m_dirtyFlag |= TRANSFORM_LOCAL_MATRIX_DIRTY_FLAG;
        m_dirtyFlag |= TRANSFORM_WORLD_MATRIX_DIRTY_FLAG;
        onNotifyTransformChanged();
    }

    const Vec3& Transform::getLocalScale() const
    {
        return m_localScale;
    }
    
    void Transform::setWorldScale(Vec3 scl)
    {
        if (m_attachedSO->getParent())
        {
            setLocalScale(scl / m_attachedSO->getParent()->getTransform()->getWorldScale());
        }
        else
        {
            setLocalScale(scl);
        }
    }

    Vec3 Transform::getWorldScale() const
    {
        if (m_attachedSO->getParent())
        {
            return m_attachedSO->getParent()->getTransform()->getWorldScale() * m_localScale;
        }
        else
        {
            return m_localScale;
        }
    }

    void Transform::onNotifyTransformChanged()
    {
        if (m_attachedSO == nullptr)
            return;
        for (auto &comp : m_attachedSO->getAllComponent())
        {
            comp->onTransformChanged();
        }
    }
}
