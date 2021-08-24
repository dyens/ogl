#include "texture.h"

class Texture {
public:
  Texture(const char* imagePath, const char* textureName, glEnum glTextureId):
    imagePath(imagePath), textureName(textureName), glTextureId(glTextureId)
  {
    int width, height, nChannels;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
  
    unsigned char* data = stbi_load(imagePath, &width, &height, &nChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      terminate("Failed to load texture");
    }
    stbi_image_free(data);
  }
  void activate() {
    pass
  };
};

