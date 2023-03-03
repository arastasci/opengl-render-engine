#pragma once
#include "engine/Transform.h"
#include "engine/ShaderProps.h"
#include "engine/Model.h"
#include "engine/Animation/Animator.h"
#include <glm/gtx/quaternion.hpp>
namespace Engine {
	class RenderObject {
	public:
		RenderObject(Transform& t, Model m, Shader* s, Animator* a);
		void Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition);


	private:
		Transform transform;
		bool isAnimated;
		Animator* animator;
		Model model;
		ShaderProps shaderProps;
		Shader* shader;

	};
}