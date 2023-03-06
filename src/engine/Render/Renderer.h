#pragma once

#include <iostream>
#include "Entity.h"
#include "engine/Core/Window.h"
#include "camera.h"
#include "Scene.h"
namespace Engine {


	class Renderer {

	public:


		Renderer(std::shared_ptr<Window> window, Scene* scene);

		void SetToPolygonMode();
	
		void RenderEntities();
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		std::shared_ptr<Window> window;
		std::vector<Entity> renderObjects;
		Scene* scene;
		void SetViewMatrix();
		void SetProjectionMatrix();
	};



}