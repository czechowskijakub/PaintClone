#include <glad.h>
#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <exception>


std::string Shader::SLoad(const char* path) {
    std::ifstream file(path);

    if (!file) { throw std::runtime_error("<<< SHADER FILE NOT FOUND >>>"); }
    if (!file.is_open()) { throw std::runtime_error("<<< CANNOT OPEN SHADER FILE >>>"); }

    std::string line;
    std::string SOut;

    while (std::getline(file, line)) {
        SOut += line + '\n';
    }

    return SOut;
}

GLuint Shader::SCompile(const char* path, GLenum type) {
    std::string source = SLoad(path);
    const char* code = source.c_str();

    GLuint OutShader = glCreateShader(type);
    glShaderSource(OutShader, 1, &code, nullptr);
    glCompileShader(OutShader);

    GLint success;
    glGetShaderiv(OutShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(OutShader, 512, nullptr, info);
        std::cerr << "<<< SHADER ERROR: " << info << " from " << path << ">>>\n";
    }

    return OutShader;
}

GLuint Shader::createSProgram() {
    GLuint vert = SCompile("Vertex/vert.glsl", GL_VERTEX_SHADER);
    GLuint frag = SCompile("Fragment/frag.glsl", GL_FRAGMENT_SHADER);

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(program, 512, nullptr, info);
        std::cerr << "<<< PROGRAM LINKING ERROR:\n" << info << "\n";
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    return program;
}

