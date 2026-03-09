#version 440 core
in vec2 vPos;
out vec4 FragColor;

uniform vec3 color = vec3(1.0, 0.0, 0.0);
uniform vec2 mousePos;
uniform float radius;

void main() {
	float dist = distance(vPos, mousePos);
	if (dist > radius) {
		discard;
	}

	FragColor = vec4(color, 1.0);
}