#pragma once
#include "engine/Transform.h"
#include "engine/ShaderProps.h"
#include "engine/Model.h"
#include "engine/Animation/Animator.h"
#include <glm/gtx/quaternion.hpp>
namespace Engine {
	class RenderObject {
	public:
		RenderObject(Transform& t, Model& m, Shader* s, Animator* a);
		RenderObject(Model& m, Shader* s, Animator* a);
		RenderObject(Model& m, Shader* s, Animator* a, PointLight* pointLight);
		void Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition);
		void SetParent(RenderObject* parent);
		void SetChild(RenderObject* child);
		void SetShader(Shader* shader);
		void SetId(int32_t id);
		void SetPointLight(PointLight* light);
		// Transform& GetTransform();
		
		Transform transform;

	private:
		void SetParentWithId(int32_t parent);
		void SetChildWithId(int32_t child);



		bool isAnimated;
		Animator* animator;
		Model model;
		Shader* shader;
		std::vector<int32_t> children;
		int32_t parent = -1;
		int32_t id;
		PointLight* pointLight;
	};
}