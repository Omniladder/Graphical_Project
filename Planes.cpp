#include "Open_GL_Basics.h"
#include "Shapes.h"
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

   

    
    Polygon Side;


    Side.makePoint(.7,.7);
    Side.makePoint(.7,-.7);
    Side.makePoint(-.7,-.7);
    Side.makePoint(-.7,.7);


    

    while(continue_run)
    {
        PreCode(window); //Code goes after here

        
        Side.draw_Polygon(window,false);
        
        
        
        continue_run = PostCode(window);
    }

    glfwTerminate();

    return 0;

}