#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec4 fragmentColor;
out vec3 fragmentNormal;
out vec3 fragmentCurrentPosition;

void main()
{
   fragmentCurrentPosition = vec3(projectionMatrix * modelMatrix * vec4(position, 1.0));
   gl_Position = projectionMatrix  * viewMatrix * modelMatrix * vec4(position, 1.0);
   fragmentColor = color;
   fragmentNormal = normalize(vec3(normalMatrix * vec4(normal, 1.0)));
}