#include <glad.h>
#include <print>
#include <vector>
#include "Window.hpp"
#include "Shader.hpp"
#include "Paint.hpp"
#include "Input.hpp"
#include "Brush.hpp"

Window::Window(int width, int height, std::string title) :
    width(width), height(height), title(title), window(nullptr), VAO(NULL), VBO(NULL), shaderProgram(NULL) {
    std::println("Window constructed!");
}

Window::~Window() {
    if (shaderProgram) glDeleteProgram(shaderProgram);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);

    if (window) glfwDestroyWindow(window);

    glfwTerminate();

    std::println("Window destructed!");
}

GLFWwindow* Window::getWindow() const {
    return window;
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

bool Window::checkGLFWInit() {
    if (!glfwInit()) {
        std::println("<<< GLFW INIT FAILED >>>");
        return false;
    }

    return true;
}

void Window::setGLFWConfig() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool Window::checkGLADInit() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println("<<< FAILED TO INITIALIZE GLAD >>>");
        return false;
    }

    return true;
}

bool Window::buildWindow() {
    if (!checkGLFWInit()) { return false; }
    setGLFWConfig();

    this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::println("<<< FAILED TO CREATE A GLFWwindow >>>");
    }
    glfwMakeContextCurrent(window);
    if (!checkGLADInit()) { return false; }
    glfwSetCursorPosCallback(window, Input::mouseCallback);
    glfwSetKeyCallback(window, Input::keyCallback);

    return true;
}

void Window::displayWindow(Paint* app) {
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    while (!glfwWindowShouldClose(window)) {
        app->canvas.bindForPainting();
        app->canvas.unbind();

        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        app->canvas.draw(app->getShader());

        //Input::processInput(window);
        glfwSwapBuffers(window);
  
        DrawTool* tool = app->getTool();
        if (tool) {
            std::println("Tool: {}\nx: {}, y: {}", tool->getName(), tool->getXPos(), tool->getYPos());
        }

        glfwPollEvents();
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::println("w {}, h {}", width, height);
}