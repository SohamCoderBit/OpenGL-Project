#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "OpenGL.h"
class Shader
{
public:
    unsigned int ShaderProgram, VertexShader, FragmentShader;

    Shader(const std::string& FilePath);
    Shader(const std::string& VertexShaderProgram, const std::string& FragmentShaderProgram);
    ~Shader();
    void LinkShaderProgram();
    void BuildAndLinkShader(const std::string& VertexShaderProgram, const std::string& FragmentShaderProgram);
    void Bind();
    int GetUniformLocation(const char* name);

private:
    int success;
    char infoLog[1024];

    struct ShaderProgramType
    {
        std::string VertexShader;
        std::string FragmentShader;
    };


    void  ShaderProgramBuild(unsigned int& ShaderName, const std::string& ShaderFile, GLenum ShaderType);
    ShaderProgramType ShaderProgramParser(const std::string& FilePath);
};