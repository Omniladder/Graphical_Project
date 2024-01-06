#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;

out vec4 vertexColor;
out vec2 vertexTexCoord;
out vec3 vertexNormal;

uniform vec3 movementDirections;
vec3 currentMovement = vec3(0.0,0.0,0.0);

void main()
{
// Pass the vertex attributes to the fragment shader
vertexColor = color;
vertexTexCoord = texture;
vertexNormal = normal;

//mat4 translationTransformation = mat4(1.0);

//translationTransformation[3][0] = movementDirections[0];
//translationTransformation[3][1] = movementDirections[1];
//translationTransformation[3][2] = movementDirections[2];


    currentMovement = currentMovement + movementDirections;


    gl_Position =  vec4(position + currentMovement,1.0);
}
