#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
namespace Engine {
	class Input {
		public:
			static void Init(GLFWwindow* window) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				lastX = 400, lastY = 300, yaw = 0, pitch = -90.f;
				firstMouse = true;
				fov = 45.f;
				MOVE_SPEED = 2.5f;
			}
			static void SetInitialCallbacks(GLFWwindow* window) {
				glfwSetCursorPosCallback(window, mouse_callback);
				glfwSetKeyCallback(window, key_callback);
				glfwSetScrollCallback(window, scroll_callback);
			}
			static void UpdateDeltaTime(float dt) {
				deltaTime = dt;
			}
			static void processInput(GLFWwindow* window)
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
			static float MOVE_SPEED;
			static float lastX, lastY;
			static float yaw;
			static float pitch ;
			static bool firstMouse;
			static float fov;
			static float deltaTime;
			 static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
				auto& io = ImGui::GetIO();
				if (io.WantCaptureMouse || io.WantCaptureKeyboard || (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)) {
					return;
				}

				Camera::camera->ProcessMouseScroll(yoffset);
			}
			static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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

				Camera::camera->ProcessMouseMovement(xOffset, yOffset);
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
