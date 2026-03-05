#pragma once
#include <glfw3.h>
#include <iostream>

class Paint;
class DrawTool;


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

    GLFWwindow* getWindow() const;

    int getWidth();
    int getHeight();

    bool checkGLFWInit();
    bool checkGLADInit();

    void setGLFWConfig();

    bool buildWindow();

    void displayWindow(Paint*);

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};