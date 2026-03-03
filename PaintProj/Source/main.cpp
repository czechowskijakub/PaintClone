#include <glfw3.h>
#include <print>
#include "Window.hpp"

int main() {
    Window window{ 640, 480, "Paint" };
    if (window.buildWindow()) {
        window.displayWindow();
    }

    return 0;
}