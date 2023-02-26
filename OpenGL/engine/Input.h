#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Engine {
	static class Input {
		public:
			static void Init(GLFWwindow* window) {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			static void SetInitialCallbacks(GLFWwindow* window) {
				glfwSetCursorPosCallback(window, mouse_callback);
				glfwSetKeyCallback(window, key_callback);
				glfwSetScrollCallback(window, scroll_callback);
			}
		private:


	};
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		auto& io = ImGui::GetIO();
		if (io.WantCaptureMouse || io.WantCaptureKeyboard || (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)) {
			return;
		}

		camera.ProcessMouseScroll(yoffset);
	}
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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

		camera.ProcessMouseMovement(xOffset, yOffset);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
}
