#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader()
{
    shaderID = 0;
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        std::ifstream vShaderFile(vertexLocation);
        std::ifstream fShaderFile(fragmentLocation);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    CompileShader(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
    GLuint sVertex, sFragment;
    GLint result;
    GLchar eLog[1024];

    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexCode, NULL);
    glCompileShader(sVertex);
    glGetShaderiv(sVertex, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(sVertex, 1024, NULL, eLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << eLog << std::endl;
        return;
    }

    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentCode, NULL);
    glCompileShader(sFragment);
    glGetShaderiv(sFragment, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(sFragment, 1024, NULL, eLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << eLog << std::endl;
        return;
    }

    // Shader Program
    shaderID = glCreateProgram();
    glAttachShader(shaderID, sVertex);
    glAttachShader(shaderID, sFragment);
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shaderID, 1024, NULL, eLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << eLog << std::endl;
        return;
    }

    // Delete shaders
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
}

GLuint Shader::GetShaderID()
{
    return shaderID;
}

GLuint Shader::GetUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(shaderID, uniformName);
}

void Shader::UseShader()
{
    glUseProgram(shaderID);
}
