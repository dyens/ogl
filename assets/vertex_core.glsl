#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 color;
out vec2 textCoord;

uniform mat4 transform; // set in code

void main() {
  gl_Position = transform * vec4(aPos, 1.0f);
  if (aPos.x < 0.0) {
    color = vec4(1.0f, 0.0f, 0.0f, 0.5f);
  }
  else if (aPos.x == 0.0) {
    color = vec4(0.0f, 1.0f, 0.0f, 0.5f);
  }
  else {
    color = vec4(0.0f, 0.0f, 1.0f, 0.5f);
  }
  textCoord = aTexCoord;
}