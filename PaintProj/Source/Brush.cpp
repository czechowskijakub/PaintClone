#include "Brush.hpp"
#include "Structures.hpp"
#include <glad.h>

std::string Brush::getName() const {
	return name;
}
Brush::Brush() {
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
		xpos + fHalfSize, ypos + fHalfSize,
		xpos - fHalfSize, ypos - fHalfSize,
		xpos + fHalfSize, ypos + fHalfSize,
		xpos + fHalfSize, ypos - fHalfSize,
		xpos - fHalfSize, ypos - fHalfSize
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fCoords), fCoords);
}

void Brush::draw(GLuint shaderID) {
	glUseProgram(shaderID);
	
	glUniform2f(glGetUniformLocation(shaderID, "mousePos"), xpos, ypos);
	glUniform1f(glGetUniformLocation(shaderID, "radius"), size / 2.f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
