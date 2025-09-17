#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight, GLint majorVer, GLint minorVer);
    ~Window();

    int initialise();

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    GLint getBufferWidth() { return bufferWidth; }
    GLint getBufferHeight() { return bufferHeight; }

private:
    GLFWwindow* mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;
    GLint majorVer, minorVer;
};

#endif
