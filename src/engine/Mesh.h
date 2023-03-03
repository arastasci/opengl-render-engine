#pragma once
#include <vector>
#include <string>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>
#include "ShaderProps.h"
#define MAX_BONE_INFLUENCE 4

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 BiTangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};
class Mesh {
public:
    // mesh data
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        m_vertices = vertices;
        m_indices = indices;
        m_textures = textures;
        setupMesh();
    };
    void Draw(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;


    void setupMesh();
};
