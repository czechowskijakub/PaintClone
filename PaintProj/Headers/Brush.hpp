#pragma once
#include "DrawTool.hpp"
#include <string>

class Brush : public DrawTool {
private:
	float size = 5;
	double xpos = 0;
	double ypos = 0;
	std::string name = "Brush";

public:
	
	std::string getName() const;

	float getSize() const override;
	double getXPos() const override;
	double getYPos() const override;

	void setSize(float) override;
	void setXPos(double) override;
	void setYPos(double) override;

	void draw() override;
};