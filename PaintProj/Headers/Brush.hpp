#pragma once
#include "DrawTool.hpp"
#include <string>

class Brush : public DrawTool {
private:
	float size = .05f;
	float xpos = 0;
	float ypos = 0;
	std::string name = "Brush";
	GLuint VBO, VAO;

public:
	
	std::string getName() const;

	Brush();

	float getSize() const override;
	float getXPos() const override;
	float getYPos() const override;

	void setSize(float) override;
	void setXPos(float) override;
	void setYPos(float) override;

	void updateCoords(float, float, float) override;

	void draw(GLuint) override;
};