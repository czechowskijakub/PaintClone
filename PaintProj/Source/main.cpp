#include <glfw3.h>
#include <print>
#include "Paint.hpp"

int main() {
    Paint paintApp;
    paintApp.init(640, 480, "Paint");
    paintApp.getWindow()->displayWindow(&paintApp); 

    return 0;
}