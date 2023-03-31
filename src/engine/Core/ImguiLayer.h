#pragma once
#include <vector>
#include <map>
#include "imgui/imgui.h"
namespace Engine {
	class Scene;
	class Entity;
	class ImGuiLayer {
	public:

		std::map<int, Entity*> pointLightEntities;
		std::map<int, Entity*> bossmenEntities;
		ImGuiLayer(Scene* scene);
		void AddPointLightEntity(Entity* e );
		void AddBossmanEntity(Entity* e);
		void RenderGUI();
		Scene* scene;

	};
}
