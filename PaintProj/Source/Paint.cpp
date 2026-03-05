#include "Paint.hpp"
#include <print>
#include "Brush.hpp"
#include "Pencil.hpp"

Paint::Paint(int width, int height) : width(width), height(height),canvas(0, 0), window(nullptr), currentTool(nullptr) {
	tools.push_back(std::make_unique<Brush>());
	tools.push_back(std::make_unique<Pencil>());
	if (!tools.empty()) {
		currentTool = tools[0].get();
	}
}

Paint::~Paint() {
	delete window;
}

GLuint Paint::getShader() {
	return screenShader;
}

Window* Paint::getWindow() {
	return window;
}

void Paint::init(std::string title) {
	this->window = new Window(width, height, title);
	if (this->window->buildWindow()) { 
		glfwSetWindowUserPointer(window->getWindow(), this); 
	}

	canvas.setSize(static_cast<int>(width * 0.9f), static_cast<int>(height * 0.9f));
	this->screenShader = Shader::createSProgram("Vertex/canvas_vert.glsl", "Fragment/canvas_frag.glsl");
	this->canvas.canvasInit();
	this->canvas.buildQuad(scale);
	glUseProgram(this->screenShader);
	glUniform1i(glGetUniformLocation(screenShader, "screenTexture"), 0);
	glUseProgram(0);
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
