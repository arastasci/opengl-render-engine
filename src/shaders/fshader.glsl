//#version 330 core
//out vec4 FragColor;
//
//
//
//struct DirLight {
//    vec3 direction;
//	
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};
//
//struct PointLight {
//    vec3 position;
//    
//    float constant;
//    float linear;
//    float quadratic;
//	
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//};
//
//struct SpotLight {
//    vec3 position;
//    vec3 direction;
//    float cutOff;
//    float outerCutOff;
//  
//    float constant;
//    float linear;
//    float quadratic;
//  
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;       
//};
//
//#define NR_POINT_LIGHTS 4
//
//in vec3 FragPos;
//in vec3 Normal;
//in vec2 TexCoord;
//
//uniform vec3 viewPos;
//uniform DirLight dirLight;
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//uniform SpotLight spotLight;
////uniform Material material;
//
//// function prototypes
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//
// void main(){
//	
//
//	vec3 norm = normalize(Normal);
//	vec3 viewDir = normalize(viewPos - FragPos);
//	
//	vec3 result = CalcDirLight(dirLight, norm, viewDir);
////	for(int i = 0; i < NR_POINT_LIGHTS; i++){
////		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
////	}
////	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
////	 result += 0.2 * vec3(texture(material.emission, TexCoord));
//	FragColor = vec4(result, 1.0);
// }
//
//
// vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
//
//
//	vec3 lightDir = normalize(light.position - fragPos);
//	float diff = max(dot(normal, lightDir), 0.0);
//
//	vec3 reflectDir = reflect(-lightDir, normal); 
////	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
//
//	float dist = length(light.position - fragPos);
//	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
//
//
//;
//
//	float theta = dot(lightDir, normalize(-light.direction));
//	float epsilon = light.cutOff - light.outerCutOff;
//	float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0); 
//	// I = (theta - gamma)/ epsilon
//	// epsilon = phi(inner cone) - gamma(outer cone)
//
//
//
//	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
//
//	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
//
//	// reflect function expects the first vector to point from the 
//	// light source towards the fragment's position 
//	vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoord));
//		/*vec3 emit = texture(material.emission,TexCoord).rgb;*/
//
//	ambient *= attenuation * intensity;
//	diffuse *= attenuation * intensity;
//	specular *= attenuation * intensity;
//
//
//	return (ambient + diffuse + specular);
//
//
//	
// }
//
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
//	vec3 lightDir = normalize(light.position - fragPos);
//	
//	float diff = max(dot(normal, lightDir), 0.0);
//
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//
//	float dist = length(light.position - fragPos);
//	float attenuation = 1.0 / (light.constant + light.linear * dist 
//	+ light.quadratic * (dist * dist));
//
//	vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord).rgb);
//    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord).rgb);
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord).rgb);
//    ambient  *= attenuation;
//    diffuse  *= attenuation;
//    specular *= attenuation;
//    return (ambient + diffuse + specular);
//}
//
// vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
//
//	vec3 lightDir = normalize(-light.direction);
//	float diff = max(dot(normal, lightDir), 0.0);
//	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//
//	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord).rgb);
//	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord).rgb);
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord).rgb);
//
//	return (ambient + diffuse + specular);
//
// }
//
//