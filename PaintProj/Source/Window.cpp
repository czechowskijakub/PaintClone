#include <glad.h>
#include <print>
#include "Shader.hpp"
#include "Window.hpp"
#include "Input.hpp"

Window::Window(int width, int height, std::string title) :
    width(width), height(height), title(title), window(nullptr), VAO(NULL), VBO(NULL), shaderProgram(NULL), currentTool(new DrawTool(5.0)) {
    std::println("Window constructed!");
}

Window::~Window() {
    if (shaderProgram) glDeleteProgram(shaderProgram);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);

    if (window) glfwDestroyWindow(window);

    delete currentTool;

    glfwTerminate();

    std::println("Window destructed!");
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
    glfwSetWindowUserPointer(window, this->currentTool);
    glfwSetCursorPosCallback(window, Input::mouseCallback);
    
    drawTriangle();

    return true;
}

void Window::displayWindow() {
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        Input::processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();

        std::println("Tools cords\nx: {}, y: {}", currentTool->getXPos(), currentTool->getYPos());
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::drawTriangle() {

    float vertices[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    shaderProgram = Shader::createSProgram();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
