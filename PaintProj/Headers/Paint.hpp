#pragma once
#include "Window.hpp"
#include "DrawTool.hpp"
#include <vector>
#include <memory>

class Paint {
private:
	Window* window = nullptr;
	DrawTool* currentTool = nullptr;

public:
	std::vector<std::unique_ptr<DrawTool>> tools;
	Paint();
	~Paint();

	Window* getWindow();
	void init(int, int, std::string);
	void setTool(DrawTool*);
	DrawTool* getTool() const;
	void chooseTool(int);
};