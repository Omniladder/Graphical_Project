#include "Open_GL_Basics.h"
#include "controls.cpp"
#include <random>
#include <iostream>


using namespace std;

int main()
{



int window_width = 800, window_height = 800;

    

GLFWwindow* window = openWindow(window_width, window_height, "My Window");

if (!window)
{return -1;} //if Window Fails to create

GLuint vID, fID, sID; //Vertex Id, fragmentation Id, Shader Id 



sID = activateShaders("libraries/shaders/vertexShader1.vert","libraries/shaders/fragShader1.frag", vID, fID); //vID is the vertex Shader fId is the fragmentation Shader

Shape triangle(17);
triangle.setVertex(0, 0, .9, 0);
triangle.setVertex(1, -.1, .7, 0);
triangle.setVertex(2, .1, .6, 0);
triangle.setVertex(3, .2, .8, 0);
triangle.setVertex(4, .3, .6, 0);
triangle.setVertex(5, .4, 0, 0);
triangle.setVertex(6, .3, -.3, 0);
triangle.setVertex(7, .3, -.5, 0);
triangle.setVertex(8, .25, -.2, 0);
triangle.setVertex(9, .2, -.5, 0);
triangle.setVertex(10, -.1, -.3, 0);
triangle.setVertex(11, -.1, -.2, 0);
triangle.setVertex(12, .1, -.1, 0);
triangle.setVertex(13, -.1, .6, 0);
triangle.setVertex(14, -.1, -.1, 0);
triangle.setVertex(15, -.3, -.2, 0);
triangle.setVertex(16, -1, 0, 0);

triangle.setTexture("textures/RonaldReagan.jpeg");

triangle.bindShape(vID);  
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

do
{
    PreCode(window, sID); //Code goes after here

    checkKey(moveObject, GLFW_KEY_W, window, .01, 'Y', sID);
    checkKey(moveObject, GLFW_KEY_S, window, -.01, 'Y', sID);
    checkKey(moveObject, GLFW_KEY_D, window, .01, 'X', sID);
    checkKey(moveObject, GLFW_KEY_A, window, -.01, 'X', sID);

    triangle.drawShape(); 
        
} while (PostCode(window));

errorCheck("CODE END");

closeWindow(vID,fID);

return 0;

}
