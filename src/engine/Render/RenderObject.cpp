#include "RenderObject.h"
namespace Engine {


	RenderObject::RenderObject(Transform& t, Model& m, Shader* s, Animator* a)
		: transform(t), animator(a), model(m), shader(s), isAnimated(a != nullptr), id(-1) {
		// TODO: move constructors for class members.
	}
	RenderObject::RenderObject(Model& m, Shader* s, Animator* a)
		: transform(), animator(a), model(m), shader(s), isAnimated(a != nullptr){}
	RenderObject::RenderObject(Model& m, Shader* s, Animator* a, PointLight* pointLight)
		: transform(), animator(a), model(m), shader(s), isAnimated(a != nullptr)
	{
		SetPointLight(pointLight);
	}
	/*Transform& RenderObject::GetTransform() {
		return transform;
	}*/
	void RenderObject::SetParent(RenderObject* parent) {
		this->parent = parent->id;
		parent->SetChildWithId(id);
	}
	void RenderObject::SetChild(RenderObject* child) {
		children.push_back(child->id);
		child->SetParentWithId(id);
	}
	void RenderObject::SetParentWithId(int32_t parent) {
		this->parent = parent;
	}
	void RenderObject::SetChildWithId(int32_t child) {
		children.push_back(child);
	}
	void RenderObject::SetId(int32_t id) {
		this->id = id;
	}
	/*
	* Sets the pointlight's position vector pointer to this object's translation transform.
	* So both of the vector pointers point to this object's translation now.
	*/
	void RenderObject::SetPointLight(PointLight* light) {
		light->position = transform.translation;
	}
	
	void RenderObject::SetShader(Shader* shader) {
		this->shader = shader;
	}
	void RenderObject::Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition) {
		glm::mat4 shaderModel = glm::mat4(1.f);
	/*	shaderModel = glm::translate(shaderModel, *transform.translation);
		shaderModel = glm::scale(shaderModel, transform.scale);*/
		//shaderModel = glm::toMat4(glm::quat(transform.rotation));
		shader->setShaderProps(shaderModel, viewMatrix, projectionMatrix, cameraPosition);
		if (isAnimated) {
			auto transforms = animator->GetFinalBoneMatrices();
			for (int i = 0; i < transforms.size(); ++i)
				shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
		}
		model.Draw(*shader);
	}
}