//
//  Component.cpp
//  Engine
//
//  Created by 蒋颂晟 on 2020/9/9.
//  Copyright © 2020 蒋颂晟. All rights reserved.
//

#include "Component.h"
#include "SceneObject.h"

namespace Canaan
{
    //-----------------------------------------------------------------------------
    Component::Component()
    {
    }

    Component::~Component()
    {
    }

    void Component::OnAttachedSceneObject(SceneObject* so)
    {
    }

    void Component::OnDetachedSceneObject(SceneObject* so)
    {
    }

    void Component::onTransformChanged()
    {
        
    }
}
