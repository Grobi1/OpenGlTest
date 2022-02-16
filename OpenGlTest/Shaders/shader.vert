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
out vec2 fragmentTexture;

void main()
{   
   gl_Position = projectionMatrix  * viewMatrix * modelMatrix * vec4(position, 1.0);
   fragmentColor = color;
   
   mat4 modelViewMatrix = viewMatrix * modelMatrix; 
   vec3 myEyeVertex = vec3(modelViewMatrix * vec4(position, 1.0));
   myEyeVertex = normalize(myEyeVertex);
   vec3 myEyeNormal = vec3(modelViewMatrix * vec4(normal, 0.0));
   vec3 reflectionVector = myEyeVertex - myEyeNormal * 2.0 * dot(myEyeVertex, myEyeNormal); 
   reflectionVector.z += 1;
   float m = 1.0 / (2.0 * sqrt(dot(reflectionVector, reflectionVector)));
   fragmentTexture = reflectionVector.xy * m + 0.5;
}