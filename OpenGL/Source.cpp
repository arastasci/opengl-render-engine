#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
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
#include <assimp/Logger.hpp>
#include <assimp/DefaultLogger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Animation.h"
#include "Animator.h"
#include "engine/Renderer.h"
#include "engine/Window.h"
#include "engine/Input.h"
using namespace Engine;
void moveLightCube(glm::vec3 &lightPos, float& radius, float& theta, float& phi);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

const float MOVE_SPEED = 2.5f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300;
float yaw = 0;
float pitch = -90.0f;
bool firstMouse = true;
float fov = 45.0f;
int main() {
	
	Window* window = Engine::Window::Create();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
	Assimp::LogStream* stderrStream = Assimp::LogStream::createDefaultStream(aiDefaultLogStream_STDERR);
	Assimp::DefaultLogger::get()->attachStream(stderrStream, Assimp::Logger::NORMAL | Assimp::Logger::DEBUGGING | Assimp::Logger::VERBOSE);

	Input::Init(window->GetGLFWwindow());
	Input::SetInitialCallbacks(window->GetGLFWwindow());
	glEnable(GL_DEPTH_TEST);

	// image loading
	stbi_set_flip_vertically_on_load(true);



	Shader lightingShader("../OpenGL/shaders/model_loading_v.glsl", "../OpenGL/shaders/model_loading_f.glsl");



	GLuint VBO;
	glGenBuffers(1, &VBO);

	// initialize imgui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");




	unsigned  int lightVAO;
	
	glGenBuffers(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader lampShader("../OpenGL/shaders/lampShader_v.glsl", "../OpenGL/shaders/lampShader_f.glsl");
	

	glm::vec3 lightPos(0.f);
	glm::vec3 offset(0.f, 0.5f, 0.f);

	glm::vec3 directionalLightDirection(glm::vec3(0.6f, -0.8f, 0.0f));
	glm::vec3 directionalLightAmbient(glm::vec3(0.1f));
	glm::vec3 directionalLightSpecular(glm::vec3(0.5f));
	glm::vec3 directionalLightDiffuse(glm::vec3(0.5f));
	float materialShininess(32.0f);
	glm::vec3 pointLightAmbient(glm::vec3(0.3f, 0.3f, 0.3f));
	glm::vec3 pointLightDiffuse(glm::vec3(1.0f));
	glm::vec3 pointLightSpecular(glm::vec3(1.0f));


	//Model backpack("../OpenGL/backpack/backpack.obj");
	lightingShader.use();
	lightingShader.setVec3("dirLight.direction", directionalLightDirection);
	lightingShader.setVec3("dirLight.ambient", directionalLightAmbient);
	lightingShader.setVec3("dirLight.specular", directionalLightSpecular);
	lightingShader.setVec3("dirLight.diffuse", directionalLightDiffuse);
	lightingShader.setFloat("material.shininess", materialShininess);

	lightingShader.setVec3("pointLight.ambient", pointLightAmbient);
	lightingShader.setVec3("pointLight.specular", pointLightSpecular);
	lightingShader.setVec3("pointLight.diffuse", pointLightDiffuse);

	lightingShader.setFloat("pointLight.constant", 1.0f);
	lightingShader.setFloat("pointLight.linear", 0.7f);
	lightingShader.setFloat("pointLight.quadratic", 1.8f);
	float radius = 2.0f;
	float phi = 0;
	float theta = 0;

	Model hand("../OpenGL/defeated/Defeated.dae");
	Animation handAnimation("../OpenGL/defeated/Defeated.dae", &hand);
	Animator animator(&handAnimation);


	Model lampModel("../opengl/lightbulb/Bombilla.obj");
	lampShader.use();
	lampShader.setFloat("material.shininess", 64.0f);
	lampShader.setVec3("dirLight.direction", directionalLightDirection);
	lampShader.setVec3("dirLight.ambient", directionalLightAmbient);
	lampShader.setVec3("dirLight.specular", directionalLightSpecular);
	lampShader.setVec3("dirLight.diffuse", directionalLightDiffuse);

	Assimp::DefaultLogger::kill();
	bool canMoveLightCube = false;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	
		
		

		 animator.UpdateAnimation(deltaTime);

		phi = glfwGetTime() * 50;
		theta = glfwGetTime() * 20;


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

	
		processInput(window);
		
	

	
		

		ImGui::Begin("Light Casters");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::BeginChild("Directional Light");
		//ImGui::BeginCombo("Directional Light", "dirLight");
		ImGui::Text("Directional Light");

		ImGui::SliderFloat3("Direction", &directionalLightDirection.x, -1.f, 1.f);
		ImGui::ColorEdit3("Ambient", &directionalLightAmbient.x);
		ImGui::ColorEdit3("Diffuse", &directionalLightDiffuse.x);
		ImGui::ColorEdit3("Specular", &directionalLightSpecular.x);
		ImGui::BeginChild("Point Light");
		ImGui::Text("Point Light");
		if (ImGui::Button("Move Light Caster Around")) {
			canMoveLightCube = !canMoveLightCube;
		}
		if (canMoveLightCube) {
			ImGui::SliderFloat("Radius", &radius, 1.25f, 2.f);
			ImGui::BeginDisabled();
			ImGui::SliderFloat3("Position", &lightPos.x, -2.f, 2.f);
			ImGui::EndDisabled();

		}
		else {
			ImGui::BeginDisabled();
			ImGui::SliderFloat("Radius", &radius, 1.25f, 2.f);
			ImGui::EndDisabled();

			ImGui::SliderFloat3("Position", &lightPos.x, -2.f, 2.f);

		}
		ImGui::ColorEdit3("Ambient", &pointLightAmbient.x);
		ImGui::ColorEdit3("Diffuse", &pointLightDiffuse.x);
		ImGui::ColorEdit3("Specular", &pointLightSpecular.x);
		ImGui::EndChild();
		ImGui::EndChild();
		
		
		ImGui::End();

		if (canMoveLightCube) moveLightCube(lightPos, radius, theta, phi);

		// camera
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		
		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(1.0f));

		lightingShader.use();
		lightingShader.setVec3("dirLight.direction", directionalLightDirection);
		lightingShader.setVec3("dirLight.ambient", directionalLightAmbient);
		lightingShader.setVec3("dirLight.specular", directionalLightSpecular);
		lightingShader.setVec3("dirLight.diffuse", directionalLightDiffuse);
		lightingShader.setVec3("pointLight.ambient", pointLightAmbient);
		lightingShader.setVec3("pointLight.specular", pointLightSpecular);
		lightingShader.setVec3("pointLight.diffuse", pointLightDiffuse);


		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", projection);
		
        auto transforms = animator.GetFinalBoneMatrices();
        for (int i = 0; i < transforms.size(); ++i)
            lightingShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

		lightingShader.setMat4("model", model);
		lightingShader.setVec3("pointLight.position", lightPos);
		hand.Draw(lightingShader);

		lampShader.use();
		lampShader.setVec3("viewPos", camera.Position);
		lampShader.setMat4("view", view);
		lampShader.setMat4("projection", projection);
		
		model = glm::translate(model, lightPos + offset);
		model = glm::scale(model, glm::vec3(2.0f));
		lampShader.setMat4("model", model);
		lampModel.Draw(lampShader);


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
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
	lightPos = glm::vec3(radius * glm::sin(glm::radians(theta)) * glm::cos(glm::radians(phi)),
		 radius * glm::sin(glm::radians(theta)) * glm::sin(glm::radians(phi)), radius * glm::cos(glm::radians(theta))) ;

}
