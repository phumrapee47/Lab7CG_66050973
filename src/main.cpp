#undef GLFW_DLL
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Libs/Shader.h"
#include "Libs/Window.h"
#include "Libs/Mesh.h"

const GLint WIDTH = 800, HEIGHT = 600;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

// Uniform locations
GLuint uniformProjection, uniformModel, uniformView;

// Vertex & Fragment Shader
static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";

void CreateTriangles()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.0f
    };

    // สร้าง Mesh 10 ตัวแยกกัน
    for (int i = 0; i < 10; i++)
    {
        Mesh* mesh = new Mesh();
        mesh->CreateMesh(vertices, indices, 12, 12);
        meshList.push_back(mesh);
    }
}

void CreateShaders()
{
    Shader* shader = new Shader();
    shader->CreateFromFiles(vShader, fShader);
    shaderList.push_back(shader);
}

int main()
{
    // สร้าง window
    mainWindow = Window(WIDTH, HEIGHT, 3, 3);
    mainWindow.initialise();

    glEnable(GL_DEPTH_TEST);

    // สร้าง Mesh และ Shader
    CreateTriangles();
    CreateShaders();

    shaderList[0]->UseShader();

    // Uniform locations
    uniformModel = shaderList[0]->GetUniformLocation("model");
    uniformProjection = shaderList[0]->GetUniformLocation("projection");
    uniformView = shaderList[0]->GetUniformLocation("view");

    // Projection matrix (perspective)
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(),
        0.1f,
        100.0f
    );
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

    // Positions ของ pyramids
    glm::vec3 pyramidPositions[] = {
        glm::vec3(0.0f, 0.0f, -2.5f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    // Loop หลัก
    while (!mainWindow.getShouldClose())
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // กล้อง
        glm::vec3 cameraPos = glm::vec3(1.0f, 0.5f, 2.0f);
        glm::vec3 cameraTarget = glm::vec3(0.0f, -0.3f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

        // วาด Mesh 10 ตัว
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, pyramidPositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::scale(model, glm::vec3(0.8f, 0.8f, 1.0f));

            glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

            meshList[i]->RenderMesh();
        }

        mainWindow.swapBuffers();
    }

    // Cleanup
    for (auto mesh : meshList) delete mesh;
    for (auto shader : shaderList) delete shader;

    return 0;
}
