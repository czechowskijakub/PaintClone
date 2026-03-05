#include <glfw3.h>
#include <print>
#include "Paint.hpp"

int main() {
    Paint paintApp{ 800, 800 };
    paintApp.init("Paint");
    paintApp.getWindow()->displayWindow(&paintApp); 

    return 0;
}