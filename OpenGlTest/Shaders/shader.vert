#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;

out vec4 fragmentColor;
out vec3 fragmentNormal;
out vec3 fragmentCurrentPosition;

void main()
{
   gl_Position = projectionMatrix  * viewMatrix * modelViewMatrix * vec4(position, 1.0);
   fragmentColor = color;
   fragmentNormal = normal;
   fragmentCurrentPosition = vec3(projectionMatrix * modelViewMatrix * vec4(position, 1.0)); // we move the camera so the vertex position is not changed
}