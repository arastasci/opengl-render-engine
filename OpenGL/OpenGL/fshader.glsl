#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 viewPos;

struct Light{


  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;


  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;

};

struct Material{
  sampler2D diffuse;
  sampler2D specular;
   sampler2D emission;
  float shininess;
};

uniform Light light;
uniform Material material;

 void main(){
	vec3 result;

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord).rgb);

	vec3 norm = normalize(Normal);


	vec3 lightDir = normalize(light.position - FragPos);
	vec3 spotDir = normalize(-light.direction);

	float theta = dot(lightDir, spotDir);
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0); // I = (theta - gamma)/ epsilon
													// epsilon = phi(inner cone) - gamma(outer cone)

	
		float dist = length(light.position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord).rgb);

		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm); 
		// reflect function expects the first vector to point from the 
		// light source towards the fragment's position 
		float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord).rgb);
		 /*vec3 emit = texture(material.emission,TexCoord).rgb;*/

		float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		diffuse *= intensity;
		specular *= intensity;


		result = (ambient + diffuse + specular /* + emit*0.1*/);
	
	FragColor = vec4(result, 1.0);
 }