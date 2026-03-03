#include "Canvas.hpp"

Canvas::Canvas(int width, int height) : width(width), height(height) {
	canvasInit();
}

void Canvas::canvasInit() {
	glGenFramebuffers(1, &FBO);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(NULL, GL_TEXTURE_2D, 0, width, height, 0, GL_RGB)

}
