#ifndef TEXTURE_H
#define TEXTURE_H

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#define STB_IMAGE_IMPLEMENTATION
// clang-format on

#include "utils.h"

// In modern OpenGL there are 4 different methods to update 2D textures:
//
// - glTexImage2D - the slowest one, recreates internal data structures.
// - glTexSubImage2D - a bit faster, but can't change the parameters (size,
// pixel format) of the image.
// - Render-to-texture with FBO - update texture entirely on GPU, very fast.
// Refer to this answer for more details:
// https://stackoverflow.com/a/10702468/1065190
// - Pixel Buffer Object PBO - for fast uploads from CPU to GPU, not supported
// (yet) on OpenGL ES.

class Texture {
 public:
  unsigned int textureId;
  const char *textureName;
  GLenum imageFormat;

  Texture(const char *textureName, const char *imagePath, GLenum imageFormat);
  Texture(const char *textureName, int width, int height, unsigned char *data,
          GLenum imageFormat);

  void activate(GLenum glTextureId);
  void deactivate();

  void subImage(GLsizei width, GLsizei height, void *pixels);

 private:
  void initGL();
  void loadImage(const char *imagePath);
  void loadPixels(unsigned char *data, int width, int height);
};

#endif
