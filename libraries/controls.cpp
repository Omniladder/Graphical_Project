#include <iostream>
#include <fstream>
#include "Shapes.h"
#include <string>
#include <GL/glew.h>
#include "thirdParty/glfw3.h" //Graphical usage
#include <unordered_map>

unordered_map<int , void*> functionMap;
unordered_map<int, void*> parameterMap;

template <typename... Args>
void checkKey(void(* calledFunction)(Args...), int key, GLFWwindow* window, Args... functionParameters)
{
    
    if(glfwGetKey(window, key) == GLFW_PRESS)
    {
        calledFunction(functionParameters...);
    }
}

void moveObject(double moveAmount, char axis, GLuint vertexShaderId) //Make sure the Char is Uppercase
{
    GLint translationVector = glGetUniformLocation(vertexShaderId ,"movementDirections");
    errorCheck("Inside move Object");

    static double xValue = 0.0;
    static double yValue = 0.0;
    static double zValue = 0.0;

    if(translationVector == -1)
    {
        std::cerr << "INVALID Shader or Uniform name ::INSIDE moveObject::" << std::endl;
        return;
    }

    switch (axis)
    {
        case 'X':
            xValue += moveAmount;

            break;
    
        case 'Y': 
            yValue += moveAmount;
            break;
    
        case 'Z':
            zValue += moveAmount;
            break;
    
        default:
        break;
    }
    glUniform3f(translationVector, xValue, yValue ,zValue);
}
