#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include "camera.h"
#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Animation.h"
#include "Animator.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void moveLightCube(glm::vec3 &lightPos, float& radius, float& theta, float& phi);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;
const float MOVE_SPEED = 2.5f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300;
float yaw = 0;
float pitch = -90.0f;
bool firstMouse = true;
float fov = 45.0f;
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}







//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetScrollCallback(window, scroll_callback);
	glEnable(GL_DEPTH_TEST);
	
	

	// image loading
	stbi_set_flip_vertically_on_load(true);

	



	Shader lightingShader("../OpenGL/model_loading_v.glsl", "../OpenGL/model_loading_f.glsl");



	GLuint VBO;
	glGenBuffers(1, &VBO);






	unsigned  int lightVAO;
	
	glGenBuffers(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader lightCubeShader("../OpenGL/lightcubev.glsl", "../OpenGL/lightcubef.glsl");
	
	

	glm::vec3 lightPos(1.2f, 1.5f, 2.0f);
	

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};
	glm::vec3 colorRed = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 colorGreen = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 colorBlue = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 colorYellow = glm::vec3(1.0f, 1.0f, 0.0f);

	glm::vec3 pointLightColors[] = { colorRed, colorGreen, colorBlue, colorYellow };

	Model backpack("../OpenGL/backpack/backpack.obj");
	lightingShader.use();
	lightingShader.setVec3("dirLight.direction", glm::vec3(0.6f, -0.8f, 0.0f));
	lightingShader.setVec3("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
	lightingShader.setVec3("dirLight.specular", glm::vec3(0.5f));
	lightingShader.setVec3("dirLight.diffuse", glm::vec3(0.5f));
	lightingShader.setFloat("material.shininess", 32.0f);

	lightingShader.setVec3("pointLight.ambient", glm::vec3(0.3f, 0.3f, 0.3f));
	lightingShader.setVec3("pointLight.specular", glm::vec3(1.0f));
	lightingShader.setVec3("pointLight.diffuse", glm::vec3(1.0f));

	lightingShader.setFloat("pointLight.constant", 1.0f);
	lightingShader.setFloat("pointLight.linear", 0.7f);
	lightingShader.setFloat("pointLight.quadratic", 1.8f);
	float radius = 2.0f;
	float phi = 0;
	float theta = 0;

	Model hand("../OpenGL/defeated/Defeated.dae");
	Animation handAnimation("../OpenGL/defeated/Defeated.dae", &hand);
	Animator animator(&handAnimation);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		animator.UpdateAnimation(deltaTime);

		phi = glfwGetTime() * 50;
		theta = glfwGetTime() * 50;
		// rendering commands;
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// camera
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		
		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(1.0f));
		lightingShader.setVec3("viewPos", camera.Position);

		lightingShader.use();
	
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", projection);
		
        auto transforms = animator.GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            lightingShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

		lightingShader.setMat4("model", model);
		lightingShader.setVec3("pointLight.position", lightPos);
		hand.Draw(lightingShader);

		lightCubeShader.use();
		lightCubeShader.setMat4("view", view);
		lightCubeShader.setMat4("projection", projection);	
		moveLightCube(lightPos, radius, phi, theta);
		
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));

		lightCubeShader.setMat4("model", model);
		
		backpack.Draw(lightCubeShader);


		
		
		
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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


void processInput(GLFWwindow* window)
{	
	float cameraSpeed = MOVE_SPEED * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	
}


void moveLightCube(glm::vec3& lightPos, float& radius, float& theta, float& phi) {
	lightPos = glm::vec3(radius * cos(glm::radians(theta)) * cos(glm::radians(theta)),
		radius * sin(glm::radians(phi)), radius * sin(glm::radians(theta)) * cos(glm::radians(phi)));

}
/*void loadTextureData(const char* filename, GLuint& textureID, GLenum format) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	
	glGenTextures(1, &textureID );

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
}
*/