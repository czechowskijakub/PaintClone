#pragma once
#include <glfw3.h>
#include "DrawTool.hpp"

class Input {
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//static void processInput(GLFWwindow* window);
	static void mouseCallback(GLFWwindow* window, double x, double y);
};