#version 440 core
in vec2 vPos;
out vec4 FragColor;

uniform vec3 color = vec3(1.0, 0.0, 0.0);
uniform vec2 mousePos;
uniform float radius;
uniform vec2 canvasScale;

void main() {
    vec2 canvasPos   = vPos / canvasScale;
    vec2 mouseCanvas = mousePos / canvasScale;

    float dist = distance(canvasPos, mouseCanvas);
    if (dist > radius) {
        discard;
    }

    FragColor = vec4(color, 1.0);
}