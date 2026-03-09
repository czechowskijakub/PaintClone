#include "Pencil.hpp"
#include <glad.h>

Pencil::Pencil() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

std::string Pencil::getName() const {
	return sName;
}

float Pencil::getSize() const {
	return size;
}

float Pencil::getXPos() const {
	return xpos;
}

float Pencil::getYPos() const {
	return ypos;
}

void Pencil::setSize(float newSize) {
	size = newSize;
}

void Pencil::setXPos(float x) {
	xpos = x;
}

void Pencil::setYPos(float y) {
	ypos = y;
}

void Pencil::updateCoords(float xpos, float ypos, float size) {
	float fHalfSize = size / 2.f;
	float fCoords[] = {
		xpos - fHalfSize, ypos + fHalfSize,
		xpos + fHalfSize, ypos + fHalfSize,
		xpos - fHalfSize, ypos - fHalfSize,
		xpos + fHalfSize, ypos + fHalfSize,
		xpos + fHalfSize, ypos - fHalfSize,
		xpos - fHalfSize, ypos - fHalfSize
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fCoords), fCoords);

}

void Pencil::draw(GLuint shaderID) {
	glUseProgram(shaderID);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
