#include "Brush.hpp"

std::string Brush::getName() const {
	return name;
}

float Brush::getSize() const {
	return size;
}

double Brush::getXPos() const {
	return xpos;
}

double Brush::getYPos() const {
	return ypos;
}

void Brush::setSize(float newSize) {
	size = newSize;
}

void Brush::setXPos(double x) {
	xpos = x;
}

void Brush::setYPos(double y) {
	ypos = y;
}

void Brush::draw() {
}
