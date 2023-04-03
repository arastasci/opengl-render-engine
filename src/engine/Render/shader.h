#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/Render/ShaderProps.h"
#include <memory>

class Shader
{
public:
    // the program ID
    unsigned int ID;
    ShaderProps* shaderProps;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath, ShaderProps* shaderProps) {
        
     //   if(shaderProps != nullptr)
           // this->shaderProps = std::make_shared<ShaderProps>(shaderProps);
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        // similiar for Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // shader Program
        ID = glCreateProgram();
            
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        // print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void initializeShaderProps(ShaderProps* props) {
        shaderProps = props;
        
    }
    void setShaderProps(glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& cameraPos) {
        use();

        setFloat("material.shininess", shaderProps->materialShininess);

        setVec3("dirLight.direction", *shaderProps->dirLightProps->direction);
        setVec3("dirLight.ambient", *shaderProps->dirLightProps->ambient);
        setVec3("dirLight.specular", *shaderProps->dirLightProps->specular);
        setVec3("dirLight.diffuse", *shaderProps->dirLightProps->diffuse);
        for (int i = 0; i < MAX_POINTLIGHT_COUNT; i++) {
            if (shaderProps->pointLightProps[i] == nullptr) continue;
            char buf[100];
            sprintf_s(buf, "pointLight[%i].init", i);
            setBool(buf, true);
            sprintf_s(buf, "pointLight[%i].position", i);            
            setVec3(buf, *shaderProps->pointLightProps[i]->position);

            sprintf_s(buf, "pointLight[%i].ambient", i);
            setVec3(buf, shaderProps->pointLightProps[i]->ambient);

            sprintf_s(buf, "pointLight[%i].specular", i);
            setVec3(buf, shaderProps->pointLightProps[i]->specular);

            sprintf_s(buf, "pointLight[%i].diffuse", i);
            setVec3(buf, shaderProps->pointLightProps[i]->diffuse);

            sprintf_s(buf, "pointLight[%i].constant", i);
            setFloat(buf, shaderProps->pointLightProps[i]->constant);

            sprintf_s(buf, "pointLight[%i].linear", i);
            setFloat(buf, shaderProps->pointLightProps[i]->linear);

            sprintf_s(buf, "pointLight[%i].quadratic", i);
            setFloat(buf, shaderProps->pointLightProps[i]->quadratic);
        }
       

        setVec3("viewPos", cameraPos);
        setMat4("view", view);
        setMat4("projection", projection);
        setMat4("model", model);
    }
    // use/activate the shader
    void use() {
        glUseProgram(ID);
    }
    // utility uniform functions
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};

#endif