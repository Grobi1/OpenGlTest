#version 330 core
in vec4 fragmentColor;
in vec3 fragmentNormal;
in vec3 fragmentCurrentPosition;
in vec2 fragmentTexture;
in vec3 fragmentCameraPosition;

uniform sampler2D sphereTexture;

out vec4 color;
void main()
{
   //vec3 lightPos;
   //lightPos.xyz = vec3(0.0, 0.0, 7);
   //vec3 cameraPos = fragmentCameraPosition;
   
   //vec3 incident = normalize(cameraPos - fragmentCurrentPosition);
   //vec3 relection = reflect(incident, fragmentNormal) *0.5 + 0.5;
   color = texture(sphereTexture, fragmentTexture.xy);
   
   
   //vec3 lightDirection = normalize(lightPos - fragmentCurrentPosition);
   //float brightness = max(dot(fragmentNormal, lightDirection), 0.05);
   //color = fragmentColor * brightness;
   //color = texture(sphereTexture, fragmentTexture);
}