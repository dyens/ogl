#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 color;

void main() {
  gl_Position = vec4(aPos, 1.0f);
  if (aPos.x < 0.0) {
    color = vec4(1.0f, 0.0f, 0.0f, 0.5f);
  }
  else if (aPos.x == 0.0) {
    color = vec4(0.0f, 1.0f, 0.0f, 0.5f);
  }
  else {
    color = vec4(0.0f, 0.0f, 1.0f, 0.5f);
  }
}