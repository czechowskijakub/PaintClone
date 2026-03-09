#include "Paint.hpp"
#include <print>
#include "Brush.hpp"
#include "Pencil.hpp"

Paint::Paint(int width, int height) : width(width), height(height), canvas(0, 0), window(nullptr), currentTool(nullptr) {

}

Paint::~Paint() {
	glDeleteProgram(screenShader);
	glDeleteProgram(brushShader);
	glDeleteProgram(pencilShader);
	delete window;
}

GLuint Paint::getShader() {
	return screenShader;
}

GLuint Paint::getPencilShader() const {
	return pencilShader; 
}

Window* Paint::getWindow() {
	return window;
}

int Paint::getWidth() const {
	return width;
}

int Paint::getHeight() const {
	return height;
}

void Paint::init(std::string title) {
	this->window = new Window(width, height, title);
	if (this->window->buildWindow()) { 
		glfwSetWindowUserPointer(window->getWindow(), this); 
	}
	canvas.setSize(static_cast<int>(width * 0.9f), static_cast<int>(height * 0.9f));
	this->pencilShader = Shader::createSProgram("Vertex/pencil_vert.glsl", "Fragment/pencil_frag.glsl");
	this->brushShader = Shader::createSProgram("Vertex/brush_vert.glsl", "Fragment/brush_frag.glsl");
	this->screenShader = Shader::createSProgram("Vertex/canvas_vert.glsl", "Fragment/canvas_frag.glsl");

	auto pencil = std::make_unique<Pencil>();
	drawShaders[pencil.get()] = this->pencilShader;
	tools.push_back(std::move(pencil));

	auto brush = std::make_unique<Brush>();
	drawShaders[brush.get()] = this->brushShader;
	tools.push_back(std::move(brush));

	if (!tools.empty()) {
		currentTool = tools[0].get();
		drawShader = drawShaders[0];
	}

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
