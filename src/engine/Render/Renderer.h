#pragma once

#include <iostream>
#include "engine/Entity/Entity.h"
#include "engine/Core/Window.h"
#include "camera.h"
#include "Scene.h"
namespace Engine {

	class Renderer {
	public:
		Renderer(std::shared_ptr<Window> window, Scene* scene);

		void SetToPolygonMode();

		/*
		* Sets the view and projection matrices and then draws all of the entities in the scene.
		*/
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