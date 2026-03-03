#pragma once
#include <glfw3.h>
#include <iostream>

class Window {
private:
    int width, height;
    std::string title;
    GLFWwindow* window;
    GLuint VAO, VBO;
    GLuint shaderProgram;

public:
    Window(int width, int height, std::string title);
    ~Window();
    void setGLFWConfig();
    bool buildWindow();
    void displayWindow();

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
};