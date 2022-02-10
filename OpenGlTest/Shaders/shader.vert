#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texture;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

out vec4 fragmentColor;
out vec3 fragmentNormal;
out vec3 fragmentCurrentPosition;
out vec2 fragmentTexture;
out vec3 fragmentCameraPosition;

void main()
{
   fragmentCurrentPosition = vec3(projectionMatrix * modelMatrix * vec4(position, 1.0));
   gl_Position = projectionMatrix  * viewMatrix * modelMatrix * vec4(position, 1.0);
   fragmentColor = color;
   fragmentNormal = normalize(vec3(normalMatrix * vec4(normal, 1.0)));
   fragmentTexture = fragmentNormal.xy * 0.5 + 0.5;
   fragmentCameraPosition = viewMatrix[3].xyz;
}