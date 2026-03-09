#pragma once
#include <glfw3.h>
#include <glad.h>

class Canvas {
	GLuint texture = 0;
	GLuint FBO = 0, VAO = 0, VBO = 0;
	int width = 0, height = 0;

public:
	float widthHeightRatio = 0;
	Canvas(int width, int height);
	~Canvas() = default;

	void canvasInit();
	void buildQuad(float scale);
	void bindForPainting();
	void unbind();
	void draw(GLuint shader);
	int getWidth();
	int getHeight();

	void setSize(int w, int h);

	GLuint getTexture() const { return texture; }
};