#include "Input.hpp"


void Input::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
}

void Input::mouseCallback(GLFWwindow* window, double x, double y) {
	DrawTool* tool = static_cast<DrawTool*>(glfwGetWindowUserPointer(window));

	if (tool) {
		tool->setXPos(x);
		tool->setYPos(y);
	}
}
