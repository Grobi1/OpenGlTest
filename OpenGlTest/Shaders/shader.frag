#version 330 core
in vec4 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentCurrentPosition;
in vec2 fragmentTexture;

uniform sampler2D sphereTexture;

out vec4 color;
void main()
{
   color = texture(sphereTexture, fragmentTexture);
}