#include "Pencil.hpp"

std::string Pencil::getName() const {
	return name;
}

float Pencil::getSize() const {
	return size;
}

double Pencil::getXPos() const {
	return xpos;
}

double Pencil::getYPos() const {
	return ypos;
}

void Pencil::setSize(float newSize) {
	size = newSize;
}

void Pencil::setXPos(double x) {
	xpos = x;
}

void Pencil::setYPos(double y) {
	ypos = y;
}

void Pencil::draw() {
}
