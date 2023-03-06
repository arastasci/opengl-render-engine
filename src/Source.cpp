#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <assimp/Importer.hpp>

#include <assimp/Logger.hpp>
#include <assimp/DefaultLogger.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "engine/Render/shader.h"
#include "engine/Render/camera.h"
#include "engine/Render/ShaderProps.h"
#include "engine/Render/Renderer.h"

#include "engine/utils/stb_image.h"

#include "engine/Core/Window.h"
#include "engine/Core/Input.h"

#include "engine/Animation/Animation.h"
#include "engine/Animation/Animator.h"

using namespace Engine;
void moveLightCube(glm::vec3 &lightPos, float& radius, float& theta, float& phi);

// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastFrame = 0.0f;


float deltaTime;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

int main() {
	
	std::shared_ptr<Window> window = Engine::Window::Create();

	Scene scene;
	Renderer renderer(window, &scene);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
	Assimp::LogStream* stderrStream = Assimp::LogStream::createDefaultStream(aiDefaultLogStream_STDERR);
	Assimp::DefaultLogger::get()->attachStream(stderrStream, Assimp::Logger::NORMAL | Assimp::Logger::DEBUGGING | Assimp::Logger::VERBOSE);

	Input input(window->GetGLFWwindow());
	input.Init();
	input.SetInitialCallbacks();
	
	
	glEnable(GL_DEPTH_TEST);

	// image loading
	stbi_set_flip_vertically_on_load(true);


	float radius = 2.0f;
	float phi = 0;
	float theta = 0;




	// initialize imgui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");


	

#pragma region Light Caster Variable Initiation
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
	float pointLightLinear = 0.7f;
	float pointLightQuadratic = 1.8f;
	float pointLightConstant = 1.f;
#pragma endregion


	Assimp::DefaultLogger::kill();

	DirLight dirLight(&directionalLightDirection,&directionalLightAmbient, &directionalLightDiffuse, &directionalLightSpecular);
	Shader lampShader("../src/shaders/lampShader_v.glsl", "../src/shaders/lampShader_f.glsl", nullptr);

	Entity* lampObject = scene.CreateEntity("../src/lightbulb/Bombilla.obj");
	lampObject->AddPointLight(PointLight(pointLightAmbient,
		pointLightDiffuse, pointLightSpecular, pointLightConstant, pointLightLinear, pointLightQuadratic));
	ShaderProps*  globalLightProps = new ShaderProps(&dirLight, lampObject->GetPointLight(), 32.f);

	lampShader.initializeShaderProps(globalLightProps);
	lampObject->SetShader(&lampShader);
	Shader lightingShader("../src/shaders/model_loading_v.glsl", "../src/shaders/model_loading_f.glsl", nullptr);
	lightingShader.initializeShaderProps(globalLightProps);
	scene.CreateEntity("../src/defeated/Defeated.dae", "../src/defeated/Defeated.dae" , &lightingShader);


	
	bool canMoveLightCube = false;
	

	while (!glfwWindowShouldClose(window->GetGLFWwindow()))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		input.UpdateDeltaTime(deltaTime);
		
		phi = glfwGetTime() * 50;
		theta = glfwGetTime() * 20;


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

	
		input.processInput();
		
		scene.UpdateAnimations(deltaTime);


	
		

		ImGui::Begin("Light Casters");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::BeginChild("Directional Light");
		//ImGui::BeginCombo("Directional Light", "dirLight");
		ImGui::Text("Directional Light");

		ImGui::SliderFloat3("Direction", &globalLightProps->dirLightProps->direction->x, -1.f, 1.f);
		ImGui::ColorEdit3("Ambient", &globalLightProps->dirLightProps->ambient->x);
		ImGui::ColorEdit3("Diffuse", &globalLightProps->dirLightProps->diffuse->x);
		ImGui::ColorEdit3("Specular", &globalLightProps->dirLightProps->specular->x);
		ImGui::BeginChild("Point Light");
		ImGui::Text("Point Light");
		if (ImGui::Button("Move Light Caster Around")) {
			canMoveLightCube = !canMoveLightCube;
		}
		if (canMoveLightCube) {
			ImGui::SliderFloat("Radius", &radius, 1.25f, 2.f);
			ImGui::BeginDisabled();
			ImGui::SliderFloat3("Position", &lampObject->transform.translation->x, -2.f, 2.f);
			ImGui::EndDisabled();
		}
		else {
			ImGui::BeginDisabled();
			ImGui::SliderFloat("Radius", &radius, 1.25f, 2.f);
			ImGui::EndDisabled();
			ImGui::SliderFloat3("Position", &lampObject->transform.translation->x, -2.f, 2.f);
		}

		ImGui::ColorEdit3("Ambient", &globalLightProps->pointLightProps->ambient.x);
		ImGui::ColorEdit3("Diffuse", &globalLightProps->pointLightProps->diffuse.x);
		ImGui::ColorEdit3("Specular", &globalLightProps->pointLightProps->specular.x);

		ImGui::EndChild();
		ImGui::EndChild();
		
		
		ImGui::End();

		if (canMoveLightCube) moveLightCube(lightPos, radius, theta, phi);
	//	lampObject->UpdatePointLight();
		renderer.RenderEntities();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwPollEvents();
		glfwSwapBuffers(window->GetGLFWwindow());
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

void moveLightCube(glm::vec3& lightPos, float& radius, float& theta, float& phi) {
	lightPos = glm::vec3(radius * glm::sin(glm::radians(theta)) * glm::cos(glm::radians(phi)),
		 radius * glm::sin(glm::radians(theta)) * glm::sin(glm::radians(phi)), radius * glm::cos(glm::radians(theta))) ;

}

