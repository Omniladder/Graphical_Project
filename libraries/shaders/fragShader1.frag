#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 vertexTexCoord;

uniform sampler2D texture1;

void main()
{
    //FragColor = vertexColor;
    FragColor = texture(texture1, vertexTexCoord);
}
