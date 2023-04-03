#pragma once
#include <glm/glm.hpp>
#include <memory>

#define MAX_POINTLIGHT_COUNT 8
struct DirLight {
	glm::vec3* direction;

	glm::vec3* ambient;
	glm::vec3* diffuse;
	glm::vec3* specular;

	DirLight() : direction(), ambient(), diffuse(), specular() {

	}

	DirLight(glm::vec3* dir, glm::vec3* amb, glm::vec3* diff, glm::vec3* spec)
		: direction(dir), ambient(amb), diffuse(diff), specular(spec) {
	}

	~DirLight() = default;
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
	int id;
	PointLight(glm::vec3 amb = glm::vec3(0.3f, 0.3f, 0.3f),
		glm::vec3 diff = glm::vec3(1.0f), glm::vec3 spec = glm::vec3(1.0f),
		float constant = 1.f, float lin = 0.7f, float quadr = 1.8f)
	{
		ambient = amb, diffuse = diff,
			specular = spec, this->constant = constant, linear = lin, quadratic = quadr;
	}

	~PointLight() = default;
};
struct ShaderProps {
	DirLight* dirLightProps;
	PointLight* pointLightProps[MAX_POINTLIGHT_COUNT];

	float materialShininess;
	int plightCount = 0;
	ShaderProps() : dirLightProps(), materialShininess(), pointLightProps() {

	}

	~ShaderProps() = default;

	ShaderProps(DirLight* dirLight, float mShininess) : pointLightProps() {
		dirLightProps = dirLight;
		materialShininess = mShininess;
	}
	bool HasPointLightSpace() {
		return MAX_POINTLIGHT_COUNT > plightCount;
	}
	void AddPointLight(PointLight* pointLight ) {
		for(int i = 0; i < MAX_POINTLIGHT_COUNT; i++){
			if(pointLightProps[i] == nullptr){
				pointLight->id = i;
				pointLightProps[i] = pointLight;
				break;
			}
		}
	}
	void RemovePointLight(int id) {
		pointLightProps[id] = nullptr;
	}
	ShaderProps(const ShaderProps& other) = default;
};

