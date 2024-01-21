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

Shape triangle(3);
triangle.setVertex(0, 0, .3);
triangle.setVertex(1, .5, .3);
triangle.setVertex(2, 0, .7);

Shape triangle1(3);
triangle1.setVertex(0, 0, -.3);
triangle1.setVertex(1, .5, -.3);
triangle1.setVertex(2, 0, .1);
//triangle.setTexture("textures/RonaldReagan.jpeg");

triangle.bindShape(vID);  
triangle1.bindShape(vID);  
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

do
{
    PreCode(window, sID); //Code goes after here

    checkKey(moveObject, GLFW_KEY_W, window, .01, 'Y', sID);
    checkKey(moveObject, GLFW_KEY_S, window, -.01, 'Y', sID);
    checkKey(moveObject, GLFW_KEY_D, window, .01, 'X', sID);
    checkKey(moveObject, GLFW_KEY_A, window, -.01, 'X', sID);

    checkKey(moveObject, GLFW_KEY_I, window, .01, 'Y', sID);
    checkKey(moveObject, GLFW_KEY_K, window, -.01, 'Y', sID);
    checkKey(moveObject, GLFW_KEY_L, window, .01, 'X', sID);
    checkKey(moveObject, GLFW_KEY_J, window, -.01, 'X', sID);


    triangle.drawShape(); 
    triangle1.drawShape(); 
        
} while (PostCode(window));

errorCheck("CODE END");

closeWindow(vID,fID);

return 0;
}
