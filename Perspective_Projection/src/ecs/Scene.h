#pragma once

// Entity Component System
#include "../Dependencies/entt/include/entt.hpp"

// Components
#include "component/TransformComponent.h"
#include "component/PointComponent.h"
#include "component/MeshComponent.h"
#include "component/TextureComponent.h"
#include "component/CameraComponent.h"

class Scene
{
private:
	entt::registry m_Registry;

public:
	Scene();
	~Scene();

	entt::entity CreateEntity();

	void OnUpdate();

};

