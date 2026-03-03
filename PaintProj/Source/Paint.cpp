#include "Paint.hpp"
#include <print>
#include "Brush.hpp"
#include "Pencil.hpp"

Paint::Paint() : window(nullptr) {
	tools.push_back(std::make_unique<Brush>());
	tools.push_back(std::make_unique<Pencil>());
	if (!tools.empty()) {
		currentTool = tools[0].get();
	}
}

Paint::~Paint() {
	delete window;
}

Window* Paint::getWindow() {
	return window;
}

void Paint::init(int width, int height, std::string title) {
	this->window = new Window(width, height, title);
	if (this->window->buildWindow()) { glfwSetWindowUserPointer(window->getWindow(), this); }
}


DrawTool* Paint::getTool() const {
	return currentTool;
}

void Paint::setTool(DrawTool* newTool) {
	currentTool = newTool;
}


void Paint::chooseTool(int index) {
	if (index >= 0 && index < tools.size()) {
		currentTool = tools[index].get();
		std::println("Switched to: {}", currentTool->getName());
	}
}
