#pragma once
#include "ImguiLayer.h"
#include "engine/Render/Scene.h"
using namespace Engine;

float uniformScale = 1.f;

ImGuiLayer::ImGuiLayer(Scene* scene) : pointLightEntities()
{
	this->scene = scene;
	
}

void ImGuiLayer::AddPointLightEntity(Entity* e)
{
	pointLightEntities.insert({e->GetPointLight()->id, e});

}
void ImGuiLayer::AddBossmanEntity(Entity* e) {
	bossmenEntities.insert({e->GetId(), e});
}

void ImGuiLayer::RenderGUI()
{
	ImGui::Begin("Light Casters");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	if (ImGui::CollapsingHeader("Directional Light")) {
		ImGui::PushID(-1);
		ImGui::Text("Directional Light");

		ImGui::SliderFloat3("Direction", &scene->shaderProps->dirLightProps->direction->x, -1.f, 1.f);
		ImGui::ColorEdit3("Ambient", &scene->shaderProps->dirLightProps->ambient->x);
		ImGui::ColorEdit3("Diffuse", &scene->shaderProps->dirLightProps->diffuse->x);
		ImGui::ColorEdit3("Specular", &scene->shaderProps->dirLightProps->specular->x);
		ImGui::PopID();
	}
	
	if (ImGui::Button("Add PointLight")) {
		Entity* e = scene->CreateEntity("../models/lightbulb/Bombilla.obj");
		scene->AddPointLight(e, PointLight());
	}
	
	for (auto& itr : pointLightEntities) {
		Entity* e = itr.second;
		char str[14];
		sprintf_s(str, "PointLight %d", e->GetPointLight()->id);
		if (ImGui::CollapsingHeader(str)) {
			ImGui::PushID(e->GetPointLight()->id);
			if (ImGui::Button("Delete PointLight")) {
				std::map<int32_t, Entity*>::iterator itrPair = pointLightEntities.find(e->GetPointLight()->id);
				int eId = e->GetId();
				int plId = e->GetPointLight()->id;
				if (itrPair != pointLightEntities.end())
				{
					pointLightEntities.erase(itrPair);
					scene->DeleteEntity(eId);
					scene->shaderProps->RemovePointLight(plId);
					ImGui::PopID();
					break;
				}
				
			}
			else {
				ImGui::SliderFloat3("Position", &e->transform.translation->x, -2.f, 2.f);

				ImGui::ColorEdit3("Ambient", &scene->shaderProps->pointLightProps[e->GetPointLight()->id]->ambient.x);
				ImGui::ColorEdit3("Diffuse", &scene->shaderProps->pointLightProps[e->GetPointLight()->id]->diffuse.x);
				ImGui::ColorEdit3("Specular", &scene->shaderProps->pointLightProps[e->GetPointLight()->id]->specular.x);
			}
			
			ImGui::PopID();
		}
	}
	ImGui::End();

	ImGui::Begin("Bossmen");
	if (ImGui::Button("Add Boss")) {
		Entity* e = scene->CreateEntity("../models/defeated/Defeated.dae", "../models/defeated/Defeated.dae");
		AddBossmanEntity(e);
	}
	for (auto& itr : bossmenEntities) {
		Entity* e = itr.second;
		char str[25];
		sprintf_s(str, "Boss with UUID %d", e->GetId() );
		if (ImGui::CollapsingHeader(str)) {
			int eId = e->GetId();
			ImGui::PushID(eId);
			if (ImGui::Button("Delete Boss")) {
				scene->DeleteEntity(eId);
				bossmenEntities.erase(eId);
				ImGui::PopID();
				break;
			}
			else {
				ImGui::SliderFloat3("Position", &bossmenEntities[e->GetId()]->transform.translation->x, -2.f, 2.f);
				ImGui::SliderFloat3("Rotation", &bossmenEntities[e->GetId()]->transform.rotation.x, -90.f, 90.f);
				ImGui::SliderFloat3("Scale", &bossmenEntities[e->GetId()]->transform.scale.x, 0.1f, 10.f);
				if (ImGui::SliderFloat("Uniform Scale", &uniformScale, 0.1f, 10.f)) {
					for (int j = 0; j < 3; j++) {
						bossmenEntities[e->GetId()]->transform.scale[j] = uniformScale;
					}
				}
			}
			
			ImGui::PopID();
		}
	}
	ImGui::End();
}
