#include "Scene.h"
namespace Engine {
	
	/*int Scene::CreateEntityWithParent(Entity* parent, Model& m, Shader* s, Animator* a) {
		Entity renderObject(m, s, a);
		renderObject.SetParent(parent);
		return AddEntityToScene(&renderObject);
	}
	Entity* Scene::CreateEntity(Model& m, Shader* s, Animator* a) {
		Entity* renderObject = new Entity(m, s, a);
		AddEntityToScene(renderObject);
		return renderObject;
	}*/
	Entity* Scene::CreateEntity(std::string&& modelPath, std::string&& animationPath, Shader* shader)
	{
		Entity* renderObject = new Entity(modelPath, animationPath, shader);
		AddEntityToScene(renderObject);
		return renderObject;
	}
	int Scene::AddEntityToScene(Entity* renderObject) {
		entityMap.insert({ nextId, renderObject });
		renderObject->SetId(nextId);
		return nextId++;
	}
	void Scene::UpdateAnimations(float& deltaTime)
	{
		for (auto& entityPair : *(GetEntityMap())) {
			
			auto& entity = entityPair.second;
			if (entity->isAnimated)
				entity->UpdateAnimation(deltaTime);
		}
	}
	std::map<int32_t, Entity*>* Scene::GetEntityMap() {
		return &entityMap;
	}
}