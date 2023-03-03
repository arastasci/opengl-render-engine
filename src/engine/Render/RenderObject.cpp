#include "RenderObject.h"

Engine::RenderObject::RenderObject(Transform& t, Model m, Shader* s, Animator* a)
	: transform(t), animator(a), model(m), shader(s), isAnimated(a != nullptr) {
	// TODO: std::move the t,a ,m
}

void Engine::RenderObject::Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition) {
	glm::mat4 shaderModel = glm::translate(shaderModel,transform.translation);
	shaderModel = glm::scale(shaderModel, transform.scale);
	shaderModel = glm::toMat4(glm::quat(transform.rotation));
	shader->setShaderProps(shaderProps, shaderModel, viewMatrix, projectionMatrix, cameraPosition);
	if (isAnimated) {
		auto transforms = animator->GetFinalBoneMatrices();
		for (int i = 0; i < transforms.size(); ++i)
			shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
	}
	model.Draw(*shader);
}