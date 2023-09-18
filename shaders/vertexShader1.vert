#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;

out vec4 fragColor;
out vec2 fragTexCoord;
out vec3 fragNormal;


void main()
{
// Pass the vertex attributes to the fragment shader
fragColor = color;
fragTexCoord = texture;
fragNormal = normal;

gl_Position = vec4(position,0);
}
