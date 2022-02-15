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

void main()
{   
   gl_Position = projectionMatrix  * viewMatrix * modelMatrix * vec4(position, 1.0);
   fragmentColor = color;
   fragmentNormal = normalize(vec3(normalMatrix * vec4(normal, 1.0)));
   
  
   fragmentCurrentPosition = normalize(vec3(viewMatrix * modelMatrix * vec4(position, 1.0)));
   vec3 cameraPos = viewMatrix[3].xyz;   
   vec3 incident = normalize(cameraPos - fragmentCurrentPosition);
   vec3 reflection = fragmentCurrentPosition - fragmentNormal * dot(fragmentCurrentPosition, fragmentNormal); 
   reflection.z += 1;
   float m = 1.0 / (sqrt(dot(reflection, reflection)));
   fragmentTexture = reflection.xy * m * 0.5 + 0.5;
}