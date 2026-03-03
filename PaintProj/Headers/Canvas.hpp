#pragma once
#include <glfw3.h>
#include <glad.h>

class Canvas {
	GLuint texture = 0;
	GLuint FBO, VAO, VBO = 0;
	int width, height;

	void buildQuad();

public:
	Canvas(int width, int height);
	~Canvas();

	void canvasInit();

	void bindForPainting();
	void unbind();
	void draw(GLuint shader);

	GLuint getTexture() const { return texture; }
};