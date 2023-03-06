#pragma once
#include <glm/glm.hpp>
#include <memory>
struct Transform {
public:
	glm::vec3* translation;
	glm::vec3 rotation;
	glm::vec3 scale;
	Transform(
		glm::vec3 r = glm::vec3(0.f,0.f,0.f), glm::vec3 s = glm::vec3(1.f)) :  rotation(r), scale(s) {
		translation = new glm::vec3();
	}
	
	
};