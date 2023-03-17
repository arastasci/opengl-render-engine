#include "Scene.h"
namespace Engine {

	Entity* Scene::CreateEntity(std::string&& modelPath, std::string&& animationPath, Shader* shader) {
		Entity* renderObject = new Entity(modelPath, animationPath, shader);
		AddEntityToScene(renderObject);
		return renderObject;
	}

	Entity* Scene::CreateEntityWithTransform(glm::vec3 position, glm::vec3 rotation,
		std::string& modelPath, std::string& animationPath, Shader* shader) {
		Entity* renderObject = new Entity(position, rotation, modelPath, animationPath, shader);
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