#include "texture.h"

// In modern OpenGL there are 4 different methods to update 2D textures:
//
// - glTexImage2D - the slowest one, recreates internal data structures.
// - glTexSubImage2D - a bit faster, but can't change the parameters (size, pixel format) of the image.
// - Render-to-texture with FBO - update texture entirely on GPU, very fast. Refer to this answer for more details: https://stackoverflow.com/a/10702468/1065190
// - Pixel Buffer Object PBO - for fast uploads from CPU to GPU, not supported (yet) on OpenGL ES.



Texture::Texture(const char* imagePath, const char* textureName, GLenum glTextureId):
    imagePath(imagePath), textureName(textureName), glTextureId(glTextureId)
{
  int width, height, nChannels;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  // TODO use vertiacally flipped textures
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(imagePath, &width, &height, &nChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    terminate("Failed to load texture");
  }
  stbi_image_free(data);
}

void Texture::activate() {
  // glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

