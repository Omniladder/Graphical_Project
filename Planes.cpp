#include "libraries/Open_GL_Basics.h"
#include "libraries/Shapes.h"
#include <random>
#include <iostream>


using namespace std;

int main()
{



int window_width = 800, window_height = 800;

    

    GLFWwindow* window = Open_window(window_width, window_height, "My Window");

    if (!window)
    {return -1;} //if Window Fails to create

    bool continue_run = true;

GLuint vID, fID, sID; 




sID = activateShaders("shaders/vertexShader1.vert","shaders/fragShader1.frag", vID, fID);


Shape triangle(4);
triangle.add_Point(0,.5);
triangle.add_Point(.5,0);
triangle.add_Point(0, -.5);

triangle.ship_Shape(vID);  

    while(continue_run)
    {
        PreCode(window, sID); //Code goes after here

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       triangle.draw_Shape(GL_TRIANGLES); 
        
        continue_run = PostCode(window);
    }

	errorCheck("CODE END");

    Close_Window(vID,fID);

    return 0;

}
