#include "Scene.h"

Scene::Scene()
{
	// Create entity and assign transform component
	entt::entity ent = m_Registry.create();
	auto& transform = m_Registry.emplace<TransformComponent>(ent);

	transform.position.x0 = 1.f;
	//m_Registry.remove<TransformComponent>(ent);
	//m_Registry.clear();

	TransformComponent& transform = m_Registry.get<TransformComponent>(ent);
	
	auto view = m_Registry.view<TransformComponent>();

	for (auto entity : view) {
		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
	}

	auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
	for (auto entity : view) {
		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
		//auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
	}
}

entt::entity Scene::CreateEntity()
{
	return m_Registry.create();
}

void Scene::OnUpdate()
{
}
