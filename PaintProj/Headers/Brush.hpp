#pragma once
#include "DrawTool.hpp"
#include <string>

class Brush : public DrawTool {
private:
	float fSize = .05f;
	float fXPos = 0;
	float fYPos = 0;
	std::string sName = "Brush";
	GLuint VBO, VAO;

public:
	
	std::string sGetName() const;

	Brush();

	float fGetSize() const override;
	float fGetXPos() const override;
	float fGetYPos() const override;

	void setSize(float) override;
	void setXPos(float) override;
	void setYPos(float) override;

	void updateCoords(float, float, float) override;

	void draw(GLuint) override;
};