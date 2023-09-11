#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;

void main()
{
// Pass the vertex attributes to the fragment shader
fragColor = color;
fragTexCoord = textureCoord;
fragNormal = normal;

gl_Position = vec4(position,0);
}
