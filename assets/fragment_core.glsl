#version 330 core

out vec4 fragColor;
in vec4 color;
in vec2 textCoord;

uniform sampler2D texture1;
uniform sampler2D mask;

void main() {
  // fragColor = vec4(1.0f, 0.2f, 0.5f, 0.8f);
  // fragColor = color;
  // fragColor = texture(texture1, textCoord);
  // fragColor = texture(mask, textCoord);
  fragColor = mix(texture(mask, textCoord), texture(texture1, textCoord), 0.5);
}