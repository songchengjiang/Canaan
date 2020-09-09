#ifndef _CN_COMPONENT_
#define _CN_COMPONENT_
#include "Prerequisites.h"
#include <rttr/type>

namespace Canaan
{
    class SceneObject;
    class Transform;
    class CN_EXPORT Component
    {
        RTTR_ENABLE()
    public:
        
        Component();
        virtual ~Component();
        
        void SetEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
        bool isEnabled() const { return m_isEnabled; }
        
        Transform* GetTransform() const;
        
        virtual void OnAttachedSceneObject(SceneObject* so);
        virtual void OnDetachedSceneObject(SceneObject* so);
        virtual void onTransformChanged();

    protected:
        
        friend class SceneObject;
        bool         m_isEnabled  = true;
        SceneObject* m_attachedSO = nullptr;
    };
}

#endif /* Component_hpp */
