#pragma once
#include <map>

#include "engine/Entity/Entity.h"
#include "engine/Core/ImguiLayer.h"
namespace Engine {
	class Scene {
	public:
		ShaderProps* shaderProps;
		Shader* lampShader;
		Shader* modelShader;
		
		/*
		* Creates an Entity and adds it to the entityMap.
		* If not animated put an empty string as parameter for the animationPath.
		*/
		Entity* CreateEntity(std::string&& modelPath, std::string&& animationPath = "", Shader* shader = nullptr);

		Entity* CreateEntityWithTransform(glm::vec3 position, glm::vec3 rotation,
			std::string& modelPath, std::string& animationPath, Shader* shader = nullptr);
		
		void AddPointLight(Entity* entity, PointLight&& pointLight);

		void BindImGuiLayer(ImGuiLayer* layer);
		void UpdateAnimations(float& deltaTime);
		std::map <int32_t, Entity*>* GetEntityMap();
		void SetShaderProps(ShaderProps* props);
		void SetModelShader(Shader* shader);
		void SetLampShader(Shader* shader);
		void DeleteEntity(int32_t id);
	private:
		int32_t nextId = 0;
		std::map <int32_t, Entity*> entityMap;
		int AddEntityToScene(Entity* renderObject);
		ImGuiLayer* layer;
	};
}