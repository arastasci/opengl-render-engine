#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
out vec4 FragColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform sampler2D texture1;

struct Light{
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct Material{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Light light;
uniform Material material;

 void main(){
   
   vec3 ambient = light.ambient * material.ambient;

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize( light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = (diff * material.diffuse) * light.diffuse;

   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm); 
   // reflect function expects the first vector to point from the 
   // light source towards the fragment's position 
   float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
   vec3 specular = material.specular * spec * light.specular;


   vec3 result = (ambient + diffuse + specular);
   FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);
 }