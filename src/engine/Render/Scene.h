#pragma once
#include "Entity.h"
#include <map>
namespace Engine {
	class Scene {
	public:
		//int CreateRenderObject(Model& m, Shader* s, Animator* a, ShaderProps* props);
	/*	Entity* CreateEntity(Model& m, Shader* s, Animator* a);*/
		Entity* CreateEntity(std::string&& modelPath, std::string&& animationPath = "", Shader* shader = nullptr);

		//int CreateEntityWithParent(Entity* parent, Model& m, Shader* s, Animator* a);
		//void DestroyEntity();
		void UpdateAnimations(float& deltaTime);
		std::map <int32_t, Entity*>* GetEntityMap();

	private:
		int32_t nextId = 0;
		std::map <int32_t, Entity*> entityMap;
		int AddEntityToScene(Entity* renderObject);
	};
}