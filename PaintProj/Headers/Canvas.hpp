#pragma once
#include <glfw3.h>
#include <glad.h>

class Canvas {
	GLuint texture = 0;
	GLuint FBO = 0, VAO = 0, VBO = 0;
	int iWidth = 0, iHeight = 0;

public:
	float fWidthHeightRatio = 0;
	Canvas(int iWidth, int iHeight);
	~Canvas() = default;

	void canvasInit();
	void buildQuad(float, int, int);
	void bindForPainting();
	void unbind();
	void draw(GLuint shader);
	int iGetWidth() const;
	int iGetHidth() const;

	void setSize(int iW, int iH);

	GLuint getTexture() const { return texture; }
};