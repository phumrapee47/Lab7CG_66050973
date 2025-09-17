#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader();
    ~Shader() {}

    // สร้าง shader จากไฟล์ vertex และ fragment
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    // ใช้งาน shader program
    void UseShader();

    // คืนค่า uniform location
    GLuint GetUniformLocation(const char* uniformName);

    // คืนค่า shader program ID
    GLuint GetShaderID();

private:
    GLuint shaderID;

    // compile shader จาก code ที่อ่านจากไฟล์
    void CompileShader(const char* vertexCode, const char* fragmentCode);
};

#endif
