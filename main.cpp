#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<sstream>
#include<string>
#include"src/shader.h"
#include"src/utils.h"
#include"src/texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define WIDTH 800
#define HEIGHT 600



void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  (void)window;
  glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


int main () {
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
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

  Shader shader = Shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

  // Verticies
  float verticies[] = {
    // shader          texture
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top left
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom right
    0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
  };

  unsigned int indicies[] = {
    0, 1, 2, // first triangle
    3, 1, 2, // second triangle
  };
  

  // VAO VBO EBO
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // Bind VAO
  glBindVertexArray(VAO);
  // Bind BO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

  // Set vertex pointer
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Set texture pointer
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  // Textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  Texture texture = Texture("assets/cat.jpg", "texture1", GL_TEXTURE0);

  shader.activate();
  shader.setInt(texture.textureName, 0);
   




  // Set EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


  glm::mat4 trans = glm::mat4(1.0f);
  // trans = glm::rotate(trans, glm::radians(0.45f), glm::vec3(0.0f, 0.0f, 1.0f));
  trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  shader.activate();
  shader.setMat4("transform", trans);

  
  while(!glfwWindowShouldClose(window)){
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 0.8f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);
    shader.activate();
    // trans = glm::rotate(trans, (float)glfwGetTime() / 100.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("transform", trans);

    // glUseProgram(shaderProgram);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();

  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VAO);
  glDeleteBuffers(1, &EBO);
  glfwTerminate();
  return 0;
}



