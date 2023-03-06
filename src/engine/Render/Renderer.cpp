#include "Renderer.h"

using namespace Engine;

	Renderer::Renderer(std::shared_ptr<Window> window, Scene* scene) {
		this->window = window;
		this->scene = scene;
	}

	void Renderer::SetToPolygonMode() {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	void Renderer::SetViewMatrix() {
		viewMatrix = Camera::Get().GetViewMatrix();
	}
	void Renderer::SetProjectionMatrix() {
		projectionMatrix = glm::perspective(glm::radians(Camera::Get().Zoom),
			static_cast<float>(window->GetScrWidth()) / static_cast<float>(window->GetScrHeight()), 0.1f, 100.0f);
	}

	
	void Renderer::RenderEntities() {
		SetViewMatrix();
		SetProjectionMatrix();
		for (auto& renderObjectPair : *(scene->GetEntityMap()))
		{
			auto& renderObject = renderObjectPair.second;

			renderObject->Draw(projectionMatrix, viewMatrix, Camera::Get().Position);
		}
	}

