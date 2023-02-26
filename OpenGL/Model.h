#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "Mesh.h"
#include <map>
#include "Animator.h"
#include "engine/ShaderProps.h"

#define MAX_BONE_WEIGHTS 4
struct BoneInfo {
    int id;
    glm::mat4 offset;
};

class Model
{
public:
    Model(std::string path);
    Model(std::string path, ShaderProps& shaderProps);
    void Draw(Shader& shader);

    std::map<std::string, BoneInfo>& GetBoneInfoMap();
    ShaderProps& GetShaderProps();
    int& GetBoneCount();

private:
    std::map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;

    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;
    ShaderProps shaderProps;


    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);
    void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

};