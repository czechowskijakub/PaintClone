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
	GLuint screenShader;
	float scale = 0.9f;
public:
	int width = 0, height = 0;
	std::vector<std::unique_ptr<DrawTool>> tools;
	Canvas canvas;
	Paint(int width, int height);
	~Paint();
	void init(std::string);
	GLuint getShader();
	Window* getWindow();
	DrawTool* getTool() const;
	void setTool(DrawTool*);
	void chooseTool(int);
};