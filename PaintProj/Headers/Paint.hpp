#pragma once
#include "Window.hpp"
#include "DrawTool.hpp"
#include "Shader.hpp"
#include "Canvas.hpp"
#include <vector>
#include <memory>

class Paint {
private:
	Window* window = nullptr;
	DrawTool* currentTool = nullptr;
	GLuint screenShader = 0;
	
	float scale = 0.9f;
	int width = 0, height = 0;
public:
	std::vector<std::unique_ptr<DrawTool>> tools;
	Canvas canvas;
	GLuint pencilShader = 0;

	Paint(int width, int height);
	~Paint();
	void init(std::string);

	GLuint getShader();
	GLuint getPencilShader() const;
	Window* getWindow();
	int getWidth() const;
	int getHeight() const;
	DrawTool* getTool() const;

	void setTool(DrawTool*);

	void chooseTool(int);
};