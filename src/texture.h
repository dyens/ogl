#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
 #include<stb_image.h>
#include <glad/glad.h>
#include "utils.h"
#include<GLFW/glfw3.h>



class Texture {
public:
  const char* imagePath;
  unsigned int textureId;
  const char *textureName;
  GLenum glTextureId;
  
  // contructor
  Texture(const char* imagePath, const char* textureName, GLenum glTextureId);
  void activate();
};

#endif
