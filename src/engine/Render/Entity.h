#pragma once
#include "engine/Transform.h"
#include "engine/ShaderProps.h"
#include "engine/Model.h"
#include "engine/Animation/Animator.h"
#include <glm/gtx/quaternion.hpp>
#include <memory>
namespace Engine {
	class Entity {
	public:
		Entity(Transform& t, Model& m, Shader* s, Animator* a);
		Entity(Model& m, Shader* s, Animator* a);
		//Entity(Model& m, Shader* s, Animator* a, PointLight&& pointLight);
		void Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition) const;
		void SetParent(Entity* parent);
		void SetChild(Entity* child);
		void SetShader(Shader* shader);
		void SetId(int32_t id);
		void AddPointLight(PointLight* light);
		void UpdatePointLight();
		PointLight* GetPointLight() const;
		// Transform& GetTransform();
		void UpdateAnimation(float& dT);
		Transform transform;
		bool isAnimated;
	private:
		void SetParentWithId(int32_t parent);
		void SetChildWithId(int32_t child);



		
		Animator* animator;
		Model model;
		Shader* shader;
		std::vector<int32_t> children;
		int32_t parent = -1;
		int32_t id;
		PointLight* pointLight;
	};
}