#version 330 core
in vec4 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentCurrentPosition;
out vec4 color;
void main()
{
   vec3 lightPos;
   lightPos.xyz = vec3(0.0, 0.0, 7);
   vec3 lightDirection = normalize(lightPos - fragmentCurrentPosition);
   float brightness = max(dot(fragmentNormal, lightDirection), 0.05);
   color = fragmentColor * brightness;
}