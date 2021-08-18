#include<iostream>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>

#include<fstream>
#include<sstream>
#include<string>

#define WIDTH 800
#define HEIGHT 600

template<typename Type>
void terminate (Type msg) {
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(1);
}



std::string loadSharedSrc(const char* filename) {

  std::ifstream file(filename);
  std::string ret;
  if (file) {
    std::ostringstream buf;
    buf << file.rdbuf();
    ret = buf.str();
  }
  else {
    // We have no format in gcc...
    std::ostringstream stringStream;
    stringStream << "Could not open file:" << filename;
    terminate(stringStream.str());
  }
  return ret;
}

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


unsigned int compileVertexShader (const char * filepath) {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  std::string vertexShaderSrc = loadSharedSrc(filepath);
  const GLchar* vertShader = vertexShaderSrc.c_str();
  glShaderSource(vertexShader, 1, &vertShader, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog [512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::ostringstream stringStream;
    stringStream << "Error with vertex shader." << std::endl
		 << "InfoLog:" << infoLog << std::endl;
    terminate(stringStream.str());
  }
  return vertexShader;
}


unsigned int compileFragmentShader (const char * filepath) {
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragmentShaderSrc = loadSharedSrc(filepath);
  const GLchar* vertShader = fragmentShaderSrc.c_str();
  glShaderSource(fragmentShader, 1, &vertShader, NULL);
  glCompileShader(fragmentShader);
  int success;
  char infoLog [512];
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::ostringstream stringStream;
    stringStream << "Error with fragment shader." << std::endl
		 << "InfoLog:" << infoLog << std::endl;
    terminate(stringStream.str());
  }
  return fragmentShader;
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
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

  // Creating shader
  unsigned int vertexShader = compileVertexShader("assets/vertex_core.glsl");
  unsigned int fragmentShader = compileFragmentShader("assets/fragment_core.glsl");

  // Creating programm
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  char infoLog [512];
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::ostringstream stringStream;
    stringStream << "Error with compilation programm." << std::endl
  		 << "InfoLog:" << infoLog << std::endl;
    terminate(stringStream.str());
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Verticies
  float verticies[] = {
    0.5f, 0.5f, 0.0f, // top right
    -0.5f, 0.5f, 0.0f, // top left
    -0.5f, -0.5f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f, // bottom right
  };

  unsigned int indicies[] = {
    0, 1, 2, // first triangle
    2, 3, 0, // second triangle
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Set EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
  
  while(!glfwWindowShouldClose(window)){
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 0.8f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    glUseProgram(shaderProgram);
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



