#pragma once
#include <glfw3.h>
#include <iostream>
#include "DrawTool.hpp"

class Window {
private:
    int width, height;
    std::string title;
    GLFWwindow* window;
    GLuint VAO, VBO;
    GLuint shaderProgram;
    DrawTool* currentTool;

public:
    Window(int width, int height, std::string title);
    ~Window();

    bool checkGLFWInit();
    bool checkGLADInit();

    void setGLFWConfig();

    bool buildWindow();

    void displayWindow();

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    void drawTriangle();
};