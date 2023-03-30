#pragma once
#include <map>

#include "engine/Entity/Entity.h"
#include "engine/Core/ImguiLayer.h"
namespace Engine {
	void SetDefaultShader(Shader* shader);
	class Scene {
	public:
		ShaderProps* shaderProps;
		Shader* defaultShader;
		
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
		void SetDefaultShader(Shader* shader);

	private:
		int32_t nextId = 0;
		std::map <int32_t, Entity*> entityMap;
		int AddEntityToScene(Entity* renderObject);
		ImGuiLayer* layer;
	};
}