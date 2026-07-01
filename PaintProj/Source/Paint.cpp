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

	int canvasW = static_cast<int>(iWidth * fScale);
	int canvasH = static_cast<int>(iHeight * fScale);
	canvas.setSize(canvasW, canvasH);
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
	int fbW, fbH;
	glfwGetFramebufferSize(window->getWindow(), &fbW, &fbH);
	this->canvas.buildQuad(fScale, fbW, fbH);
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

void Paint::onResize(int newWidth, int newHeight) {
	iWidth = newWidth;
	iHeight = newHeight;

	int canvasW = static_cast<int>(iWidth * fScale);
	int canvasH = static_cast<int>(iHeight * fScale);

	canvas.setSize(canvasW, canvasH);
	canvas.canvasInit();
	canvas.buildQuad(fScale, iWidth, iHeight);
	glViewport(0, 0, iWidth, iHeight);
}
