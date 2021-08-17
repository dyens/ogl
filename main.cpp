#include<iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>

#define WIDTH 800
#define HEIGHT 600

void terminate (const char* msg) {
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(1);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main () {
  std::cout << "hello world" << std::endl;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Dyens test", NULL, NULL);
  if (window == NULL) {
    terminate("Can not create the window");
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    terminate("Failed to initialize GLAD");
  } 

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

  while(!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);
    
    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // check and call events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}


