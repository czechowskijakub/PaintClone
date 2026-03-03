#include "DrawTool.hpp"
#include <print>

DrawTool::DrawTool(float size) : size(size), xpos(0), ypos(0) {
	
}

DrawTool::~DrawTool() {

}

double DrawTool::getXPos() {
	return xpos;
}

double DrawTool::getYPos() {
	return ypos;
}

void DrawTool::setXPos(double newX) {
	xpos = newX;
}

void DrawTool::setYPos(double newY) {
	ypos = newY;
}
