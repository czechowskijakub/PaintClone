#pragma once
#include <glfw3.h>
#include <string>

class DrawTool {
public:
	virtual ~DrawTool() = default;

	virtual std::string sGetName() const = 0;
	virtual float fGetSize() const = 0;
	virtual float fGetXPos() const = 0;
	virtual float fGetYPos() const = 0;

	virtual void setSize(float) = 0;
	virtual void setXPos(float) = 0;
	virtual void setYPos(float) = 0;

	virtual void updateCoords(float xpos, float ypos, float size) = 0;

	virtual void draw(GLuint) = 0;
};