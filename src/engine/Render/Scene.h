#pragma once
#include "Entity.h"
#include <map>
namespace Engine {
	class Scene {
	public:

		/*
		* Creates an Entity and adds it to the entityMap. 
		* If not animated put an empty string as parameter for the animationPath.
		*/
		Entity* CreateEntity(std::string&& modelPath, std::string&& animationPath = "", Shader* shader = nullptr);

		void UpdateAnimations(float& deltaTime);
		std::map <int32_t, Entity*>* GetEntityMap();

	private:
		int32_t nextId = 0;
		std::map <int32_t, Entity*> entityMap;
		int AddEntityToScene(Entity* renderObject);
	};
}