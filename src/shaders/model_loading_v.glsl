#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;
void main()
{
    mat4 BoneTransform;
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES) 
        {
            break;
        }
        BoneTransform +=  weights[i] * finalBonesMatrices[boneIds[i]];
        
        
    }
    vec4 totalPosition = BoneTransform * vec4(pos, 1.0);

    FragPos = vec3(model * totalPosition);
    Normal = vec3(model * transpose(inverse(BoneTransform)) * vec4(norm, 1.0));
    mat4 viewModel = view * model;
    gl_Position =  projection * viewModel * totalPosition;
    TexCoords = tex;
}