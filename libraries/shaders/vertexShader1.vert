#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;
layout(location = 4) in uint objectId;

out vec4 vertexColor;
out vec2 vertexTexCoord;
out vec3 vertexNormal;

uniform mat4 movementDirections = mat4(1.0);


void main()
{

	// Pass the vertex attributes to the fragment shader
	vertexColor = color;
	vertexTexCoord = texture;
	vertexNormal = normal;


	gl_Position = movementDirections * vec4(position, 1.0);
}
