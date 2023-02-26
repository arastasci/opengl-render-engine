#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace Engine {
	class Window {
	public:
		static Window* Create() {
			return &Window();
		}
		Window() {
			glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RenderEngine", NULL, NULL);
			if (window == NULL)
			{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				
			}
			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		}
		
		GLFWwindow* GetGLFWwindow() {
			return window;
		}
	private:
		GLFWwindow* window;
		const int SCR_WIDTH = 1920;
		const int SCR_HEIGHT = 1080;
		
	};
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
