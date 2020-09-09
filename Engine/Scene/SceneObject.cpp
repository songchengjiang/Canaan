//
//  SceneObject.cpp
//  Engine
//
//  Created by 蒋颂晟 on 2020/9/9.
//  Copyright © 2020 蒋颂晟. All rights reserved.
//

#include "SceneObject.h"

namespace Canaan
{
    SceneObject::SceneObject()
    : m_transform(new Transform)
    {
        m_transform->m_attachedSO = this;
    }
    SceneObject::~SceneObject()
    {
        removeAllComponents();
    }

    Component* SceneObject::addComponentBy(const std::string &ctype)
    {
        rttr::variant var = rttr::type::get_by_name(ctype).create();
        bool converted_ok = false;
        std::shared_ptr<Component> comp = var.convert<std::shared_ptr<Component>>(&converted_ok);
        if (!converted_ok)
            return nullptr;
        comp->m_attachedSO = this;
        comp->OnAttachedSceneObject(this);
        m_componentList.push_back(comp);
        return comp.get();
    }

    void SceneObject::removeFirstComponentBy(const std::string &ctype)
    {
        auto iter = findComponentBy(ctype);
        if (iter != m_componentList.end())
        {
            (*iter)->m_attachedSO = nullptr;
            (*iter)->OnDetachedSceneObject(this);
            m_componentList.erase(iter);
        }
    }

    Component* SceneObject::getFirstComponentBy(const std::string &ctype)
    {
        auto iter = findComponentBy(ctype);
        if (iter != m_componentList.end())
            return (*iter).get();
        return nullptr;
    }

    void SceneObject::removeComponents(const std::string &ctype)
    {
        for (std::vector<std::shared_ptr<Component>>::iterator iter = m_componentList.begin(); iter != m_componentList.end();)
        {
            if ((**iter).get_type().get_name().to_string() == ctype)
            {
                (*iter)->m_attachedSO = nullptr;
                (*iter)->OnDetachedSceneObject(this);
                iter = m_componentList.erase(iter);
            }
            else
                ++iter;
        }
    }

    void SceneObject::removeAllComponents()
    {
        for (auto &comp : m_componentList)
        {
            comp->m_attachedSO = nullptr;
            comp->OnDetachedSceneObject(this);
        }
        m_componentList.clear();
    }

    std::vector<Component*> SceneObject::getComponentsBy(const std::string &ctype)
    {
        std::vector<Component*> compList;
        for (auto &comp : m_componentList)
        {
            if ((*comp).get_type().get_name().to_string() == ctype)
            {
                compList.push_back(comp.get());
            }
        }
        return compList;
    }

    std::vector<std::shared_ptr<Component>>::iterator SceneObject::findComponentBy(const std::string &ctype)
    {
        auto iter = std::find_if(m_componentList.begin(), m_componentList.end(), [ctype](const std::shared_ptr<Component> &compPtr) -> bool{
            return (*compPtr).get_type().get_name().to_string() == ctype;
         });
        return iter;
    }

    void SceneObject::addChild(const std::shared_ptr<SceneObject>& child)
    {
        child->m_parent = this;
        m_children.push_back(child);
    }

    void SceneObject::removeChild(const std::shared_ptr<SceneObject>& child)
    {
        m_children.erase(std::find(m_children.begin(), m_children.end(), child));
    }

}
