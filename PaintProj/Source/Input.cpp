#include "Input.hpp"
#include "Paint.hpp"

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {

            int index = key - GLFW_KEY_1;
            Paint* paintApp = static_cast<Paint*>(glfwGetWindowUserPointer(window));

            float coords[2] = { paintApp->getTool()->fGetXPos(), paintApp->getTool()->fGetYPos() };

            if (paintApp) {
                paintApp->chooseTool(index);
                paintApp->getTool()->setXPos(coords[0]);
                paintApp->getTool()->setYPos(coords[1]);

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
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float fScale = 0.9f;
        float ndcX = ((static_cast<float>(x) / width) * 2.0f - 1.0f) / fScale;
        float ndcY = (1.0f - (static_cast<float>(y) / height) * 2.0f) / fScale;

        app->getTool()->setXPos(ndcX);
        app->getTool()->setYPos(ndcY);
    }
}

bool Input::isLMBPressed(GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
        return true;
    }

    return false;
}
