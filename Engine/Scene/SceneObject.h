#ifndef _CN_SCENE_OBJECT_
#define _CN_SCENE_OBJECT_
#include "Prerequisites.h"
#include "Component.h"
#include "Transform.h"
#include <rttr/registration>

namespace Canaan
{
    class Scene;
    class CN_EXPORT SceneObject
    {
    public:
        
        SceneObject();
        ~SceneObject();
        
        void setName(const std::string& name) { m_name = name; }
        const std::string& getName() const { return m_name; }
        
        Transform* getTransform() { return m_transform.get(); }
        
        Component* addComponentBy(const std::string &ctype);
        void removeFirstComponentBy(const std::string &ctype);
        Component* getFirstComponentBy(const std::string &ctype);
        
        template<class T>
        T* addComponent();
        
        template<class T>
        T* getFirstComponent();
        
        template<class T>
        void removeFirstComponent();
        
        void removeComponents(const std::string &ctype);
        std::vector<Component*> getComponentsBy(const std::string &ctype);
        
        template<class T>
        std::vector<T*> getComponents();
        
        const std::vector<std::shared_ptr<Component>>& getAllComponent() const { return m_componentList; }
        
        void removeAllComponents();
        
        void addChild(const std::shared_ptr<SceneObject>& child);
        void removeChild(const std::shared_ptr<SceneObject>& child);
        size_t getChildrenCount() const { return m_children.size(); }
        
        SceneObject* getParent() { return m_parent; }
        
    private:
        
        std::vector<std::shared_ptr<Component>>::iterator findComponentBy(const std::string &type);
        
    private:
        
        std::string                             m_name;
        std::unique_ptr<Transform>              m_transform;
        std::vector<std::shared_ptr<Component>> m_componentList;
        
        std::vector<std::shared_ptr<SceneObject>> m_children;
        SceneObject* m_parent;
    };

    template<class T>
    T* SceneObject::addComponent()
    {
        return static_cast<T*>(addComponentBy(rttr::type::get<T>().get_name().to_string()));
    }

    template<class T>
    T* SceneObject::getFirstComponent()
    {
        return static_cast<T*>(getFirstComponentBy(rttr::type::get<T>().get_name().to_string()));
    }

    template<class T>
    void SceneObject::removeFirstComponent()
    {
        removeFirstComponentBy(rttr::type::get<T>().get_name().to_string());
    }

    template<class T>
    std::vector<T*> SceneObject::getComponents()
    {
        std::vector<T*> compList;
        for (auto &comp : m_componentList)
        {
            if ((*comp).get_type().get_name() == rttr::type::get<T>().get_name())
            {
                compList.push_back(static_cast<T*>(comp.get()));
            }
        }
        return compList;
    }
}

#endif
