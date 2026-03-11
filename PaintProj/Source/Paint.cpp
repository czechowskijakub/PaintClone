#include "Paint.hpp"
#include <print>
#include "Brush.hpp"
#include "Pencil.hpp"

Paint::Paint(int iWidth, int iHeight) : iWidth(iWidth), iHeight(iHeight), canvas(0, 0), window(nullptr), currentTool(nullptr) {

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

int Paint::iGetWidth() const {
	return iWidth;
}

int Paint::iGetHidth() const {
	return iHeight;
}

void Paint::init(std::string title) {
	this->window = new Window(iWidth, iHeight, title);
	if (this->window->buildWindow()) { 
		glfwSetWindowUserPointer(window->getWindow(), this); 
	}
	canvas.setSize(static_cast<int>(iWidth * 0.9f), static_cast<int>(iHeight * 0.9f));
	this->pencilShader = Shader::createSProgram("Vertex/pencil_vert.glsl", "Fragment/pencil_frag.glsl");
	this->brushShader = Shader::createSProgram("Vertex/brush_vert.glsl", "Fragment/brush_frag.glsl");
	this->screenShader = Shader::createSProgram("Vertex/canvas_vert.glsl", "Fragment/canvas_frag.glsl");

	auto pencil = std::make_unique<Pencil>();
	um_drawShaders[pencil.get()] = this->pencilShader;
	tools.push_back(std::move(pencil));

	auto brush = std::make_unique<Brush>();
	um_drawShaders[brush.get()] = this->brushShader;
	tools.push_back(std::move(brush));

	if (!tools.empty()) {
		currentTool = tools[0].get();
		drawShader = um_drawShaders[0];
	}

	this->canvas.canvasInit();
	this->canvas.buildQuad(fScale);
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
		std::println("Switched to: {}", currentTool->sGetName());
	}
}
