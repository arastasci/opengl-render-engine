#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "engine/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include "engine/Render/camera.h"

#include "engine/Model.h"
#include <assimp/Logger.hpp>
#include <assimp/DefaultLogger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "engine/utils/stb_image.h"
#include "engine/Render/Renderer.h"
#include "engine/Core/Window.h"
#include "engine/Input.h"
#include "engine/ShaderProps.h"

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



	Shader lightingShader("../OpenGL/shaders/model_loading_v.glsl", "../OpenGL/shaders/model_loading_f.glsl");




	// initialize imgui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");


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

	DirLight dirLight(&directionalLightDirection,&directionalLightAmbient, &directionalLightDiffuse, &directionalLightSpecular);
	PointLight pointLight(&lightPos, &pointLightAmbient,
		&pointLightDiffuse, &pointLightSpecular, &pointLightConstant, &pointLightLinear, &pointLightQuadratic);
	ShaderProps props(&dirLight, &pointLight, 32.f);


	
	float radius = 2.0f;
	float phi = 0;
	float theta = 0;
	Scene scene;
	Renderer renderer(window, &scene);

	Model boss("../OpenGL/defeated/Defeated.dae", props);
	Animation bossAnimation("../OpenGL/defeated/Defeated.dae", &boss);
	Animator animator(&bossAnimation);
	Transform t;
	scene.CreateRenderObject(t, boss, &lightingShader, &animator);

	Shader lampShader("../OpenGL/shaders/lampShader_v.glsl", "../OpenGL/shaders/lampShader_f.glsl");

	Model lampModel("../opengl/lightbulb/Bombilla.obj", props);
	
	scene.CreateRenderObject(t, lampModel, &lampShader, nullptr);

	Assimp::DefaultLogger::kill();
	bool canMoveLightCube = false;
	

	while (!glfwWindowShouldClose(window->GetGLFWwindow()))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		input.UpdateDeltaTime(deltaTime);
		
		
			
		animator.UpdateAnimation(deltaTime);

		phi = glfwGetTime() * 50;
		theta = glfwGetTime() * 20;


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

	
		input.processInput();
		
	

	
		

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
		
		//glm::mat4 view = Camera::Get().GetViewMatrix();
		
		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(1.0f));

		//lightingShader.setShaderProps(props, model, view, projection, Camera::Get().Position);
		renderer.RenderObjects();
		

		
		/*boss.Draw(lightingShader);
		
		
		model = glm::translate(model, lightPos + offset);
		model = glm::scale(model, glm::vec3(2.0f));
		lampShader.setShaderProps(props, model, view, projection, Camera::Get().Position);
		
		lampModel.Draw(lampShader);*/


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
