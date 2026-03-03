#pragma once
#include <glfw3.h>
#include <string>

class DrawTool {
public:
	virtual ~DrawTool() = default;

	virtual std::string getName() const = 0;
	virtual float getSize() const = 0;
	virtual double getXPos() const = 0;
	virtual double getYPos() const = 0;

	virtual void setSize(float) = 0;
	virtual void setXPos(double) = 0;
	virtual void setYPos(double) = 0;

	virtual void draw() = 0;
};