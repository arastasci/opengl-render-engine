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
		Entity(std::string& modelPath, std::string& animationPath, Shader* shader = nullptr);

		/*
		* Gets the MVP matrix and draws the entity to the screen.
		*/
		void Draw(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::vec3& cameraPosition) const;
		/*
		* Sets the parent of this entity to the provided entity and sets this entity as the child of the provided entity.
		*/
		void SetParent(Entity* parent);
		/*
		* Sets the provided entity as the child of this entity, and sets this entity as the parent of the provided entity.
		*/
		void SetChild(Entity* child);
		/*
		* Sets the shader that's going to be used for this entity in a draw call.
		*/
		void SetShader(Shader* shader);
		/*
		* Sets the UUID of this entity.
		*/
		void SetId(int32_t id);
		/*
		* Adds a point light caster to this entity that can later be embedded to a shader.
		*/
		void AddPointLight(PointLight&& light);
		PointLight* GetPointLight() const;
		// Transform& GetTransform();
		void UpdateAnimation(float& dT);
		Transform transform;
		bool isAnimated;
	private:
		/*
		* This method makes this entity the parent of the entity with provided id.
		* This method gets called when the latter entity binds itself as the child
		* of this entity.
		*/
		void SetParentWithId(int32_t parent);
		/*
		* This method makes this entity the child of the entity with provided id.
		* This method gets called when the latter entity binds itself as the parent
		* of this entity.
		*/
		void SetChildWithId(int32_t child);



		std::unique_ptr<Animation> animation;
		std::unique_ptr<Animator> animator;
		Model model;
		Shader* shader;
		std::vector<int32_t> children;
		int32_t parent = -1;
		int32_t id;
		PointLight* pointLight;
	};
}