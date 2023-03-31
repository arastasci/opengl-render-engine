#pragma once
#include "Transform.h"
#include "engine/Render/ShaderProps.h"
#include "Model/Model.h"
#include "Animation/Animator.h"
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include "engine/Render/shader.h"
namespace Engine {
	void SetDefaultShader(Shader* shader);
	class Entity {
	public:
		Transform transform;
		bool isAnimated;
		Entity(Transform& t, Model& m, Shader* s, Animator* a);
		
		Entity(glm::vec3 position, glm::vec3 rotation, 
			std::string& modelPath, std::string& animationPath, Shader* shader);
		
		Entity(Model& m, Shader* s, Animator* a);
		
		~Entity(); 
		
		Entity(std::string& modelPath, std::string& animationPath, Shader* shader);

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
		int32_t GetId();
		/*
		* Adds a point light caster to this entity that can later be embedded to a shader.
		*/
		void AddPointLight(PointLight&& light);

		
		PointLight* GetPointLight() const;
		
		void UpdateAnimation(float& dT);
	private:
		
		Model model;
		Shader* shader;
		PointLight* pointLight;

		std::unique_ptr<Animation> animation;
		std::unique_ptr<Animator> animator;

		std::vector<int32_t> children;
		int32_t parent = -1;
		int32_t id;


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


	};
}