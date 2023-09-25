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


Shape triangle(3);
triangle.add_Point(-800,-800);
triangle.add_Point(0,0);
triangle.add_Point(800,800);

triangle.ship_Shape(vID);  

    while(continue_run)
    {
        PreCode(window, sID); //Code goes after here

        
       triangle.draw_Shape(GL_TRIANGLES); 
        
        continue_run = PostCode(window);
    }

    Close_Window(vID,fID);

    return 0;

}
