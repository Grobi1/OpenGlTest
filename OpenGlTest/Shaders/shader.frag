#version 330 core
in vec4 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentCurrentPosition;
out vec4 color;
void main()
{
   vec3 lightPos;
   lightPos.xyz = vec3(1.0, 1.0, -0.0);
   vec3 lightDirection = normalize(lightPos - fragmentCurrentPosition);
   float diffuse = max(dot(fragmentNormal, lightDirection), 0.0f);
   diffuse = max(diffuse, 0.1); //Simulate ambient light
   color = fragmentColor * diffuse;
}