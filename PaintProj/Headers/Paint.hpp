#pragma once
#include "Window.hpp"
#include "DrawTool.hpp"
#include "Shader.hpp"
#include "Canvas.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

class Paint {
private:
	Window* window = nullptr;
	DrawTool* currentTool = nullptr;
	GLuint screenShader = 0;
	
	float fScale = 0.9f;
	int iWidth = 0, iHeight = 0;
public:
	std::vector<std::unique_ptr<DrawTool>> tools;
	std::unordered_map<DrawTool*, GLuint> um_drawShaders;
	Canvas canvas;
	GLuint drawShader = 0;
	GLuint pencilShader = 0;
	GLuint brushShader = 0;

	Paint(int width, int height);
	~Paint();
	void init(std::string);

	GLuint getShader();
	GLuint getPencilShader() const;
	Window* getWindow();
	int iGetWidth() const;
	int iGetHidth() const;
	DrawTool* getTool() const;

	void setTool(DrawTool*);

	void chooseTool(int);
};