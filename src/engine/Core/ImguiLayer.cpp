#pragma once
#include "ImguiLayer.h"
#include "engine/Render/Scene.h"
using namespace Engine;

ImGuiLayer::ImGuiLayer(Scene* scene) : pointLightEntities()
{
	this->scene = scene;
	
}

void ImGuiLayer::AddPointLightEntity(Entity* entity)
{
	pointLightEntities.push_back(entity);

}

void ImGuiLayer::RenderGUI()
{
	ImGui::Begin("Light Casters");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::CollapsingHeader("Directional Light")) {
		ImGui::Text("Directional Light");

		ImGui::SliderFloat3("Direction", &scene->shaderProps->dirLightProps->direction->x, -1.f, 1.f);
		ImGui::ColorEdit3("Ambient", &scene->shaderProps->dirLightProps->ambient->x);
		ImGui::ColorEdit3("Diffuse", &scene->shaderProps->dirLightProps->diffuse->x);
		ImGui::ColorEdit3("Specular", &scene->shaderProps->dirLightProps->specular->x);
	}
	
	if (ImGui::Button("Add PointLight")) {
		Entity* e = scene->CreateEntity("../models/lightbulb/Bombilla.obj");
		scene->AddPointLight(e, PointLight());
	}
	for (int i = 0; i < pointLightEntities.size(); i++) {
		char str[14];
		sprintf_s(str, "PointLight %d", i);
		if (ImGui::CollapsingHeader(str)) {
			ImGui::SliderFloat3("Position", &pointLightEntities[i]->transform.translation->x, -2.f, 2.f);

			ImGui::ColorEdit3("Ambient", &scene->shaderProps->pointLightProps[i]->ambient.x);
			ImGui::ColorEdit3("Diffuse", &scene->shaderProps->pointLightProps[i]->diffuse.x);
			ImGui::ColorEdit3("Specular", &scene->shaderProps->pointLightProps[i]->specular.x);
		}
	}



	ImGui::End();
}
