#include "Scene.h"
namespace Engine {

	Entity* Scene::CreateEntity(std::string&& modelPath, std::string&& animationPath, Shader* shader) {
		if (shader == nullptr && modelPath != "../models/defeated/Defeated.dae")
			shader = lampShader;
		else
			shader = modelShader;
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

	void Scene::AddPointLight(Entity* entity , PointLight&& pointLight)
	{
		
		if (shaderProps->HasPointLightSpace()) {
			entity->AddPointLight(PointLight(pointLight));
			layer->AddPointLightEntity(entity);
			shaderProps->AddPointLight(entity->GetPointLight());
			
		}
		else {
			std::cout << "Cannot instantiate point light, maximum amount reached" << std::endl;
		}
	}

	int Scene::AddEntityToScene(Entity* renderObject) {
		entityMap.insert({ nextId, renderObject });
		renderObject->SetId(nextId);
		return nextId++;
	}

	void Scene::BindImGuiLayer(ImGuiLayer* layer)
	{
		this->layer = layer;
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

	void Scene::SetShaderProps(ShaderProps* props)
	{
		shaderProps = props;
	}
	
	void Scene::SetLampShader(Shader* shader) {
		lampShader = shader;
	}
	void Scene::SetModelShader(Shader* shader) {
		modelShader = shader;
	}
}