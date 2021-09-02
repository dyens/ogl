#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "shader.h"
#include "texture.h"
#include "utils.h"
#define STB_IMAGE_IMPLEMENTATION

#define WIDTH 1024
#define HEIGHT 768
#define VSYNC false
#define SWAPTEXTURE false

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // REMOVE VSYNC !!!
  glfwWindowHint(GLFW_DOUBLEBUFFER, VSYNC);

  GLFWwindow *window =
      glfwCreateWindow(WIDTH, HEIGHT, "Dyens test", NULL, NULL);
  if (window == NULL) {
    terminate("Can not create the window");
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    terminate("Failed to initialize GLAD");
  }

  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  Shader shader =
      Shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

  // Verticies
  float verticies[] = {
      // shader          texture
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // top left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  // bottom right
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
  };

  unsigned int indicies[] = {
      0, 1, 2,  // first triangle
      3, 1, 2,  // second triangle
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Set texture pointer
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Setup textures
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  int catWidth, catHeight, catNChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *catData =
      stbi_load("assets/cat.jpg", &catWidth, &catHeight, &catNChannels, 0);
  if (!catData) {
    terminate("Failed to load texture");
  }

  int dogWidth, dogHeight, dogNChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *dogData =
      stbi_load("assets/dog.jpg", &dogWidth, &dogHeight, &dogNChannels, 0);
  if (!dogData) {
    terminate("Failed to load texture");
  }

  // Texture texture = Texture("texture1", "assets/dog.jpg");
  Texture texture = Texture("texture1", catWidth, catHeight, catData);

  shader.activate();
  // TODO: 0 -> GL_TEXTURE0
  shader.setInt(texture.textureName, 0);

  // Set EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies,
               GL_STATIC_DRAW);

  glm::mat4 trans = glm::mat4(1.0f);
  // trans = glm::rotate(trans, glm::radians(0.45f), glm::vec3(0.0f,
  // 0.0f, 1.0f));
  trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  shader.activate();
  shader.setMat4("transform", trans);

  double lastTime = glfwGetTime();
  int nbFrames = 0;
  bool isDogShowed = false;
  while (!glfwWindowShouldClose(window)) {
    // Show FPS
    nbFrames++;
    double currentTime = glfwGetTime();
    if (currentTime - lastTime >=
        1.0) {  // If last prinf() was more than 1 sec ago
      // printf and reset timer
      std::cout << "FPS:" << nbFrames << std::endl;
      nbFrames = 0;
      lastTime += 1.0;
    }
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 0.8f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (SWAPTEXTURE) {
      if (isDogShowed) {
        texture.subImage(catWidth, catHeight, catData);
        isDogShowed = false;
      } else {
        texture.subImage(dogWidth, dogHeight, dogData);
        isDogShowed = true;
      }
    }
    texture.activate(GL_TEXTURE0);
    glBindVertexArray(VAO);
    shader.activate();
    // trans = glm::rotate(trans, (float)glfwGetTime() / 100.0f, glm::vec3(0.0f,
    // 0.0f, 1.0f));
    trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("transform", trans);

    // glUseProgram(shaderProgram);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    // glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VAO);
  glDeleteBuffers(1, &EBO);

  stbi_image_free(catData);
  stbi_image_free(dogData);
  glfwTerminate();
  return 0;
}
