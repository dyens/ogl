#include "texture.h"

Texture::Texture(const char *textureName, const char *imagePath,
                 GLenum imageFormat)
    : textureName(textureName), imageFormat(imageFormat) {
  initGL();
  loadImage(imagePath);
}

Texture::Texture(const char *textureName, int width, int height,
                 unsigned char *data, GLenum imageFormat)
    : textureName(textureName), imageFormat(imageFormat) {
  initGL();
  if (data) {
    loadPixels(data, width, height);
  } else {
    // TODO: window should close
    terminate("Failed to load texture");
  }
}

void Texture::activate(GLenum glTextureId) {
  glActiveTexture(glTextureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::deactivate() { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture::subImage(GLsizei width, GLsizei height, void *pixels) {
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, imageFormat,
                  GL_UNSIGNED_BYTE, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::initGL() {
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::loadImage(const char *imagePath) {
  int width, height, nChannels;
  // TODO use vertiacally flipped textures
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(imagePath, &width, &height, &nChannels, 0);
  if (data) {
    loadPixels(data, width, height);
  } else {
    // TODO: window should close
    terminate("Failed to load texture");
  }
  stbi_image_free(data);
}

void Texture::loadPixels(unsigned char *data, int width, int height) {
  glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, imageFormat,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}
