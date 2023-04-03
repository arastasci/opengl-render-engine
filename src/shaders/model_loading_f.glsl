#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;


struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight{
	bool init;
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};
struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;    
    float shininess;
};
const int MAX_POINTLIGHT_COUNT = 8;


uniform DirLight dirLight;
uniform PointLight pointLight[MAX_POINTLIGHT_COUNT];
uniform Material material;
uniform vec3 viewPos;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
 vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
void main()
{    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 norm = normalize(Normal);
    vec3 result;
	result += CalcDirLight(dirLight, norm, viewDir);
	for(int i = 0; i < MAX_POINTLIGHT_COUNT; i++){
		if(!pointLight[i].init) continue;	
		
		result += CalcPointLight(pointLight[i], norm, FragPos, viewDir);

	}
    FragColor = vec4(result, 1.0);
}


 vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){

	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords).rgb);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords).rgb);
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords).rgb);

	return (ambient + diffuse + specular);

 }
 vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    
	vec3 lightDir = normalize(light.position - fragPos);
	
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist 
	+ light.quadratic * (dist * dist));

	vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, TexCoords).rgb);
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, TexCoords).rgb);
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords).rgb);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
