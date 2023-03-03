#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;


uniform mat4 transform;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = norm;
    TexCoords = tex;
    FragPos = vec3(model * vec4(aPos,1.0));
    
}