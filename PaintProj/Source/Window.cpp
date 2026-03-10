#include <glad.h>
#include <print>
#include <vector>
#include <memory>
#include "Window.hpp"
#include "Shader.hpp"
#include "Paint.hpp"
#include "Input.hpp"
#include "Brush.hpp"

Window::Window(int iWidth, int iHeight, std::string title) :
    iWidth(iWidth), iHeight(iHeight), sTitle(sTitle), window(nullptr), VAO(NULL), VBO(NULL), shaderProgram(NULL) {
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

int Window::iGetWidth() const {
    return iWidth;
}

int Window::iGetHeight() const {
    return iHeight;
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

    this->window = glfwCreateWindow(iWidth, iHeight, sTitle.c_str(), nullptr, nullptr);
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
        if (Input::isLMBPressed(window)) {
            app->canvas.bindForPainting();
            glViewport(0, 0, app->canvas.iGetWidth(), app->canvas.iGetHidth());

            DrawTool* tool = app->getTool();
            if (tool) {
                GLuint shaderToUse = app->um_drawShaders[tool];
                std::println("Tool: {}\nx: {}, y: {}", tool->sGetName(), tool->fGetXPos(), tool->fGetYPos());
                tool->updateCoords(tool->fGetXPos(), tool->fGetYPos(), tool->fGetSize());
                tool->draw(shaderToUse);
            } else {
                std::println("<<< ERROR: currentTool is NULL >>>");
            }
            
            
            app->canvas.unbind();
        }
        
        app->canvas.unbind();

        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        app->canvas.draw(app->getShader());
        
        //Input::processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int iWidth, int iHeight) {
    glViewport(0, 0, iWidth, iHeight);
    std::println("w {}, h {}", iWidth, iHeight);
}