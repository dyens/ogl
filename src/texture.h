#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include <glad/glad.h>
#include "utils.h"
#include<GLFW/glfw3.h>



class Texture {
public:
  unsigned int textureId;
  unsigned int textureName;
  glEnum glTextureId;
  
  // contructor
  Texture(const char* imagePath, const char* textureName, glEnum glTextureId);
  void activate();
};

#endif
