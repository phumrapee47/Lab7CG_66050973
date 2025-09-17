#include "Window.h"
#include <iostream>

Window::Window()
{
    width = 800;
    height = 600;
    majorVer = 3;
    minorVer = 3;
}

Window::Window(GLint windowWidth, GLint windowHeight, GLint majorVer, GLint minorVer)
{
    width = windowWidth;
    height = windowHeight;
    this->majorVer = majorVer;
    this->minorVer = minorVer;
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

int Window::initialise()
{
    if (!glfwInit())
    {
        std::cout << "GLFW init failed!" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
    if (!mainWindow)
    {
        std::cout << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW init failed!" << std::endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, bufferWidth, bufferHeight);

    return 0;
}
