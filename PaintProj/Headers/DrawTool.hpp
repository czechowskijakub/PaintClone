#pragma once
#include <glfw3.h>

class DrawTool {
private:
	double xpos = 0.0;
	double ypos = 0.0;
	float size;
public:
	DrawTool(float size = 5.f);
	~DrawTool();
	double getXPos();
	double getYPos();

	void setXPos(double);
	void setYPos(double);

};