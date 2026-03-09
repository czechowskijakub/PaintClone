#include "Brush.hpp"
#include <glad.h>

std::string Brush::getName() const {
	return name;
}

float Brush::getSize() const {
	return size;
}

float Brush::getXPos() const {
	return xpos;
}

float Brush::getYPos() const {
	return ypos;
}

void Brush::setSize(float newSize) {
	size = newSize;
}

void Brush::setXPos(float x) {
	xpos = x;
}

void Brush::setYPos(float y) {
	ypos = y;
}

void Brush::updateCoords(float xpos, float ypos, float size) {
	float fHalfSize = size / 2.f;
	float fCoords[] = {
		xpos - fHalfSize, ypos + fHalfSize,
		xpos - fHalfSize, ypos - fHalfSize,
		xpos + fHalfSize, ypos - fHalfSize,
		xpos + fHalfSize, ypos + fHalfSize,
		xpos + fHalfSize, ypos - fHalfSize,
		xpos - fHalfSize, ypos - fHalfSize
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fCoords), fCoords);

}

void Brush::draw(GLuint) {

}
