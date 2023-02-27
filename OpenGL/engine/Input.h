#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"


Camera* Camera::camera;

namespace Engine {
	class Input {
		public:
			static Input* singleton;
			enum CallbackType {
				MOUSE_POSITION = 0,
				SCROLL,
				KEY
			};
			Input() {
				if (singleton) return;
				singleton = this;
				

			}
			void Init(GLFWwindow* window) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			
			}

			void SetInitialCallbacks(GLFWwindow* window) {
				glfwSetCursorPosCallback(window, mouse_callback);
				glfwSetKeyCallback(window, key_callback);
				glfwSetScrollCallback(window, scroll_callback);
			}
			

			void UpdateDeltaTime(float dt) {
				deltaTime = dt;
			}
			void processInput(GLFWwindow* window)
			{
				auto& io = ImGui::GetIO();
				if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
					return;
				}

				float cameraSpeed = MOVE_SPEED * deltaTime;




				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(window, true);
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
					Camera::camera->ProcessKeyboard(FORWARD, deltaTime);
				}
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
					Camera::camera->ProcessKeyboard(BACKWARD, deltaTime);
				}
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
					Camera::camera->ProcessKeyboard(LEFT, deltaTime);
				}
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
					Camera::camera->ProcessKeyboard(RIGHT, deltaTime);
				}

			}
		
	private:
		float deltaTime = 0.f;
			

	};
}

