#pragma once
#include <glfw3.h>
#include <string>


struct Shader {
	static std::string SLoad(const char* path);
	static GLuint SCompile(const char* path, GLenum type);
	static GLuint createSProgram();
};