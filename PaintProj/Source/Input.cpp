#include "Input.hpp"
#include "Paint.hpp"

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
            int index = key - GLFW_KEY_1;
            Paint* paintApp = static_cast<Paint*>(glfwGetWindowUserPointer(window));

            if (paintApp) {
                paintApp->chooseTool(index);
            }
        }
    }
}
/*
void Input::processInput(GLFWwindow* window) {
	int inputKey = 0;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
}
*/
void Input::mouseCallback(GLFWwindow* window, double x, double y) {
    Paint* app = static_cast<Paint*>(glfwGetWindowUserPointer(window));

    if (app && app->getTool()) {
        app->getTool()->setXPos(x);
        app->getTool()->setYPos(y);
    }
}
