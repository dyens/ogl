#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"utils.h"

void terminate (const char* msg) {
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(1);
}


