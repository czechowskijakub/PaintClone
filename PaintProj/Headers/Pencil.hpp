#pragma once
#include "DrawTool.hpp"
#include <vector>

class Pencil : public DrawTool {
private:
	float fSize = .02f;
	float fXPos = 0;
	float fYPos = 0;
	std::string sName = "Pencil";
	GLuint VBO, VAO;
	GLuint drawShader = 0;
public:
	Pencil();

	std::string sGetName() const override;

	float fGetSize() const override;
	float fGetXPos() const override;
	float fGetYPos() const override;

	void setSize(float) override;
	void setXPos(float) override;
	void setYPos(float) override;

	void updateCoords(float, float, float) override;

	void draw(GLuint) override;
};


/*
	to do:
	make an array that stores tool's coords, and
	with every mouse callback - update them, so we can color a rectangle upon pressing LMB.
*/