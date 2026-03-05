#version 440 core

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;

void main() {
    vec4 col = texture(screenTexture, TexCoords);
    if(col.a < 0.1) FragColor = vec4(1.0, 0.0, 0.0, 1.0); 
    else FragColor = col;
}