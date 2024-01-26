#version 330 core

in vec2 TextureCoords;

out vec4 pixelColor;

uniform sampler2D texture1;

void main() {
  pixelColor = texture2D(texture1, TextureCoords);
}