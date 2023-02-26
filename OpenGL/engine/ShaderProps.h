#pragma once
#include <glm/glm.hpp>


struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	DirLight() {

	}
	DirLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec)
		: direction(dir), ambient(amb), diffuse(diff), specular(spec) {
	}
};
struct PointLight {
public:
	glm::vec3* position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	PointLight(glm::vec3* pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float lin, float quadr)
	{
		position = pos, ambient = amb, diffuse = diff, specular = spec, linear = lin, quadratic = quadr;
	}
};
struct ShaderProps {
public:
	DirLight dirLightProps;
	PointLight* pointLightProps;
	float materialShininess;
	ShaderProps() {
		
	}
	ShaderProps(DirLight dirLight, PointLight* pointLight) {
		pointLightProps = pointLight;
		dirLightProps = dirLight;
	}

};

