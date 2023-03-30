#pragma once
#include <vector>
#include "imgui/imgui.h"
namespace Engine {
	class Scene;
	class Entity;
	class ImGuiLayer {
	public:

		std::vector<Entity*> pointLightEntities;
		std::vector<Entity*> bossmenEntities;
		ImGuiLayer(Scene* scene);
		void AddPointLightEntity(Entity* e );
		void AddBossmanEntity(Entity* e);
		void RenderGUI();
		Scene* scene;

	};
}
