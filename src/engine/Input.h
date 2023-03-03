#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/Render/camera.h"
#include "engine/Core/Window.h"



namespace Engine {

	class Input {
		public:
			enum CallbackType {
				MOUSE_POSITION = 0,
				SCROLL,
				KEY
			};
			Input(GLFWwindow* window) {
			
				this->window = window;

			}
			void Init() {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			
			}
			void SetInitialCallbacks() {
				glfwSetCursorPosCallback(window, mouse_callback);
				glfwSetKeyCallback(window, key_callback);
				glfwSetScrollCallback(window, scroll_callback);
			}
			void UpdateDeltaTime(float dt) {
				deltaTime = dt;
			}
			void processInput()
			{
				auto& io = ImGui::GetIO();
				if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
					return;
				}

				float cameraSpeed = MOVE_SPEED * deltaTime;




				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					glfwSetWindowShouldClose(window, true);
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
					Camera::Get().ProcessKeyboard(FORWARD, deltaTime);
				}
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
					Camera::Get().ProcessKeyboard(BACKWARD, deltaTime);
				}
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
					Camera::Get().ProcessKeyboard(LEFT, deltaTime);
				}
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
					Camera::Get().ProcessKeyboard(RIGHT, deltaTime);
				}

			}
		
			
	private:
		float deltaTime = 0.f;
		GLFWwindow* window;

		static inline const float MOVE_SPEED = 2.5f;
		static inline float lastX = 400, lastY = 300;
		static inline float yaw = 0.f;
		static inline float pitch = -90.f;
		static inline bool firstMouse = true;
		static inline float fov = 45.f;
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
			auto& io = ImGui::GetIO();
			if (io.WantCaptureMouse || io.WantCaptureKeyboard || (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)) {
				return;
			}

			Camera::Get().ProcessMouseScroll(yoffset);
		}
		static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
		{
			auto& io = ImGui::GetIO();
			if (io.WantCaptureMouse || io.WantCaptureKeyboard || (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)) {
				return;
			}

			float xpos = (float)xposIn;
			float ypos = (float)yposIn;
			if (firstMouse) {
				lastX = xpos;
				lastY = xpos;
				firstMouse = false;
			}
			float xOffset = xpos - lastX;
			float yOffset = lastY - ypos;
			lastX = xpos;
			lastY = ypos;

			Camera::Get().ProcessMouseMovement(xOffset, yOffset);
		}

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_Q && action == GLFW_PRESS)
			{
				if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				else
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				}
			}
		}
			
	};
}


