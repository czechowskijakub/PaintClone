#pragma once
#include <glfw3.h>
#include <iostream>

class Paint;
class DrawTool;


class Window {
private:
    int iWidth, iHeight;
    std::string sTitle;
    GLFWwindow* window;
    GLuint VAO, VBO;
    GLuint shaderProgram;

public:
    Window(int iWidth, int iHeight, std::string sTitle);
    ~Window();

    GLFWwindow* getWindow() const;

    int iGetWidth() const;
    int iGetHeight() const;

    bool checkGLFWInit();
    bool checkGLADInit();

    void setGLFWConfig();

    bool buildWindow();

    void displayWindow(Paint*);

    static void framebufferSizeCallback(GLFWwindow* window, int iWidth, int iHeight);
};