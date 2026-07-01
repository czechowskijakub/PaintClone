#include "Spray.hpp"
#include <glad.h>

Spray::Spray() {

}

std::string Spray::sGetName() const{
	return sName;
}

float Spray::fGetSize() const {
	return fSize;
}

float Spray::fGetXPos() const
{
	return fXPos;
}

float Spray::fGetYPos() const
{
	return fYPos;
}

void Spray::setSize(float newSize) {
	fSize = newSize;
}

void Spray::setXPos(float x) {
	fXPos = x;
}

void Spray::setYPos(float y) {
	fYPos = y;
}

void Spray::updateCoords(float fXPos, float fYPos, float size) {
	float fHalfSize = size / 2.f;
	float fCoords[] = {
		fXPos - fHalfSize, fYPos + fHalfSize,
		fXPos + fHalfSize, fYPos + fHalfSize,
		fXPos - fHalfSize, fYPos - fHalfSize,
		fXPos + fHalfSize, fYPos + fHalfSize,
		fXPos + fHalfSize, fYPos - fHalfSize,
		fXPos - fHalfSize, fYPos - fHalfSize
	};
}

void Spray::draw(GLuint shaderID) {
	glUseProgram(shaderID);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

