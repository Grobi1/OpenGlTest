#version 330 core
in vec4 fragmentColor;
in vec2 fragmentTexture;

uniform sampler2D sphereTexture;

out vec4 color;
void main()
{
   color = texture(sphereTexture, fragmentTexture);
}