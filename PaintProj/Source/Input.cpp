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
        int winW, winH, fbW, fbH;
        glfwGetWindowSize(window, &winW, &winH);
        glfwGetFramebufferSize(window, &fbW, &fbH);
        if (winW <= 0 || winH <= 0 || fbW <= 0 || fbH <= 0) { return; }

        float scaleX = static_cast<float>(fbW) / static_cast<float>(winW);
        float scaleY = static_cast<float>(fbH) / static_cast<float>(winH);
        float xFb = static_cast<float>(x) * scaleX;
        float yFb = static_cast<float>(y) * scaleY;

        float canvasW = static_cast<float>(app->canvas.iGetWidth());
        float canvasH = static_cast<float>(app->canvas.iGetHidth());
        float offsetX = (static_cast<float>(fbW) - canvasW) * 0.5f;
        float offsetY = (static_cast<float>(fbH) - canvasH) * 0.5f;

        float xRel = xFb - offsetX;
        float yRel = yFb - offsetY;

        if (canvasW == 0.0f || canvasH == 0.0f) { return; }

        float u = xRel / canvasW;
        float v = yRel / canvasH;

        float ndcX = u * 2.0f - 1.0f;
        float ndcY = 1.0f - 2.0f * v;

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
