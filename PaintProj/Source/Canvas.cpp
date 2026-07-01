#include "Canvas.hpp"
#include "Shader.hpp"
#include <print>

Canvas::Canvas(int iWidth, int iHeight) : iWidth(iWidth), iHeight(iHeight) {
}
void Canvas::setSize(int iW, int iH) {
	iWidth = iW;
	iHeight = iH > 0 ? iH : 1;
	fWidthHeightRatio = static_cast<float>(iH) / static_cast<float>(iW);
}

void Canvas::buildQuad(float fScale, int iFbWidth, int iFbHeight) {
	if (iFbWidth <= 0) { iFbWidth = 1; }
	if (iFbHeight <= 0) { iFbHeight = 1; }

	float sX = static_cast<float>(iWidth) / static_cast<float>(iFbWidth);
	float sY = static_cast<float>(iHeight) / static_cast<float>(iFbHeight);

	float canvasVertices[] = {
		-sX,  sY,   0.0f, 1.0f,
		-sX, -sY,   0.0f, 0.0f,
		 sX, -sY,   1.0f, 0.0f,

		-sX,  sY,   0.0f, 1.0f,
		 sX, -sY,   1.0f, 0.0f,
		 sX,  sY,   1.0f, 1.0f
	};

	if (VAO) { glDeleteVertexArrays(1, &VAO); }
	if (VBO) { glDeleteBuffers(1, &VBO); }

	auto shaderProgram = Shader::createSProgram("Vertex/canvas_vert.glsl", "Fragment/canvas_frag.glsl");
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(canvasVertices), canvasVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Canvas::canvasInit() {
	if (texture) glDeleteTextures(1, &texture);
	if (FBO) glDeleteFramebuffers(1, &FBO);

	glGenFramebuffers(1, &FBO);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// white first
	glViewport(0, 0, iWidth, iHeight);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Canvas::bindForPainting() {
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glViewport(0, 0, iWidth, iHeight);
}

void Canvas::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Canvas::draw(GLuint shader) {
	glUseProgram(shader);

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

int Canvas::iGetWidth() const {
	return iWidth;
}
int Canvas::iGetHidth() const {
	return iHeight;
};


