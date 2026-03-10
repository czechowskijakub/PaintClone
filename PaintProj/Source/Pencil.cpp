#include "Pencil.hpp"
#include <glad.h>
#include "Shader.hpp"

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

std::string Pencil::sGetName() const {
	return sName;
}

float Pencil::fGetSize() const {
	return fSize;
}

float Pencil::fGetXPos() const {
	return fXPos;
}

float Pencil::fGetYPos() const {
	return fYPos;
}

void Pencil::setSize(float newSize) {
	fSize = newSize;
}

void Pencil::setXPos(float x) {
	fXPos = x;
}

void Pencil::setYPos(float y) {
	fYPos = y;
}

void Pencil::updateCoords(float fXPos, float fYPos, float size) {
	float fHalfSize = size / 2.f;
	float fCoords[] = {
		fXPos - fHalfSize, fYPos + fHalfSize,
		fXPos + fHalfSize, fYPos + fHalfSize,
		fXPos - fHalfSize, fYPos - fHalfSize,
		fXPos + fHalfSize, fYPos + fHalfSize,
		fXPos + fHalfSize, fYPos - fHalfSize,
		fXPos - fHalfSize, fYPos - fHalfSize
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fCoords), fCoords);

}

void Pencil::draw(GLuint shaderID) {
	glUseProgram(shaderID);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
