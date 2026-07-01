#version 440 core
in vec2 vPos;
out vec4 FragColor;

uniform vec3 color = vec3(1.0, 0.0, 0.0);

void main() {
    FragColor = vec4(color, 1.0);
}