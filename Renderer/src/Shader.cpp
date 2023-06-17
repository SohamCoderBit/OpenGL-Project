#include "Shader.h"		


Shader::Shader(const std::string& FilePath)
{
    ShaderProgramType ParsedShaderProgram = ShaderProgramParser(FilePath);
    BuildAndLinkShader(ParsedShaderProgram.VertexShader, ParsedShaderProgram.FragmentShader);
}

Shader::Shader(const std::string& VertexShaderProgram, const std::string& FragmentShaderProgram)
{
    BuildAndLinkShader(VertexShaderProgram, FragmentShaderProgram);
}

Shader::~Shader()
{
    glDeleteProgram(ShaderProgram);
}

void Shader::LinkShaderProgram()
{
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED :: " << infoLog << std::endl;
    }

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

}
void Shader::BuildAndLinkShader(const std::string& VertexShaderProgram, const std::string& FragmentShaderProgram)
{
    ShaderProgramBuild(VertexShader, VertexShaderProgram, GL_VERTEX_SHADER);
    ShaderProgramBuild(FragmentShader, FragmentShaderProgram, GL_FRAGMENT_SHADER);
    LinkShaderProgram();
}
void Shader::Bind()
{
    glUseProgram(ShaderProgram);
}

int Shader::GetUniformLocation(const char* name)
{
    int uniID;
    uniID = glGetUniformLocation(ShaderProgram, name);
    return uniID;
}


void Shader::ShaderProgramBuild(unsigned int& ShaderName, const std::string& ShaderFile, GLenum ShaderType)
{
    const char* ShaderSource = ShaderFile.c_str();
    ShaderName = glCreateShader(ShaderType);
    glShaderSource(ShaderName, 1, &ShaderSource, nullptr);
    glCompileShader(ShaderName);

    glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "Compile Error : Shader " << std::endl;
    }
}

Shader::ShaderProgramType Shader::ShaderProgramParser(const std::string& FilePath)
{

    std::ifstream stream(FilePath);
    std::string line;
    std::vector<std::string> ShaderCode(2);

    enum class ShaderType
    {
        None = -1, Vertex = 0, Fragment = 1
    };

    ShaderType Type = ShaderType::None;

    while (std::getline(stream, line))
    {
        if (std::strstr(line.c_str(), "#Shader") != nullptr)
        {
            if (std::strstr(line.c_str(), "Vertex") != nullptr)
            {
                Type = ShaderType::Vertex;
            }
            else if (std::strstr(line.c_str(), "Fragment") != nullptr)
            {
                Type = ShaderType::Fragment;
            }
        }
        else
        {
            ShaderCode[(int)Type] += line + "\n";
        }
    }

    return { ShaderCode[0] , ShaderCode[1] };
}
