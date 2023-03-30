#pragma once
#include <vector>
#include "imgui/imgui.h"
namespace Engine {
	class Scene;
	class Entity;
	class ImGuiLayer {
	public:

		std::vector<Entity*> pointLightEntities;

		ImGuiLayer(Scene* scene);
		void AddPointLightEntity(Entity* entity);

		void RenderGUI();
		Scene* scene;

	};
}
