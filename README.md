# Paint Clone (OpenGL)

My graphics project, helping me understand how CPU - GPU communication works.

Framebuffer Rendering (FBO): Unlike simple apps that clear the screen every frame, this project renders to a seperate texture.
This allows for a persistent canvas, where every brush move is stored in GPU memory.

Shader programs (Vertex, Fragments): Written in GLSL (v440) for texture mapping and coordinate transformations.

## Technologies
Project language: C++23
Graphics API: OpenGL 4.4
