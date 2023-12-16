#include "Open_GL_Basics.h"
#include "Polygons.h"
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


Polygon triangle;
triangle.set_Point(0,0,.5, 0, 255, 0, 0);
triangle.set_Point(1,.5,0, 0, 255, 0 ,0);
triangle.set_Point(2,0, -.5, 0, 255, 0, 0);

triangle.output_Polygon();

triangle.bind_Polygon(vID);  
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

while(continue_run)
{
    PreCode(window, sID); //Code goes after here

    triangle.draw_Polygon(GL_TRIANGLES); 
        
    continue_run = PostCode(window);
}

errorCheck("CODE END");

Close_Window(vID,fID);

return 0;

}
