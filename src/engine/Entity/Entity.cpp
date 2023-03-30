#include "Entity.h"
namespace Engine {

	Entity::Entity(glm::vec3 position, glm::vec3 rotation, std::string& modelPath, std::string& animationPath, Shader* shader)
		: model(modelPath), shader(shader), transform() {
		if (animationPath == "")
			return;
		isAnimated = true;

		animation = std::make_unique<Animation>(animationPath, &model);
		animator = std::make_unique<Animator>(animation.get());

		transform.translation = new glm::vec3(position);
		transform.rotation = rotation;
	}

	Entity::~Entity() {
		delete& animation;
	}

	Entity::Entity(std::string& modelPath, std::string& animationPath, Shader* shader)
		: model(modelPath), shader(shader) {
		if (animationPath == "") return;
		isAnimated = true;
		animation = std::make_unique<Animation>(animationPath, &model);
		animator = std::make_unique<Animator>(animation.get());
	}

	void Entity::SetParent(Entity* parent) {
		this->parent = parent->id;
		parent->SetChildWithId(id);
	}
	void Entity::SetChild(Entity* child) {
		children.push_back(child->id);
		child->SetParentWithId(id);
	}
	void Entity::SetParentWithId(int32_t parent) {
		this->parent = parent;
	}
	void Entity::SetChildWithId(int32_t child) {
		children.push_back(child);
	}
	void Entity::SetId(int32_t id) {
		this->id = id;
	}
	void Entity::AddPointLight(PointLight&& light)
	{
		pointLight = new PointLight(light);
		pointLight->position = transform.translation;
	}
	

	PointLight* Entity::GetPointLight() const {
		return pointLight;
	}
	void Entity::UpdateAnimation(float& dT) {
		animator->UpdateAnimation(dT);
	}

	void Entity::SetShader(Shader* shader) {
		this->shader = shader;
	}

	void Entity::Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition) const {

		glm::mat4 shaderModel = glm::mat4(1.f);
		shaderModel = glm::translate(shaderModel, *transform.translation);
		shaderModel = glm::scale(shaderModel, transform.scale);
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