#include <iostream>
//#include <fstream>
#include "Shapes.h"
//#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "thirdParty/glfw3.h" //Graphical usage


template <typename... Args>
void checkKey(void(* calledFunction)(Args...), int key, GLFWwindow* window, Args... functionParameters)
{
    
    if(glfwGetKey(window, key) == GLFW_PRESS)
    {
        calledFunction(functionParameters...);
    }
}

void moveObject(double moveAmount, char axis, GLuint vertexShaderId, Shape shapeToTransform) //Make sure the Char is Uppercase
{
	ClearErrors();
	GLint translationVector = glGetUniformLocation(vertexShaderId ,"transformationMatrix");
//	GLint uniformId = glGetUniformLocation(vertexShaderId ,"moveId");
	errorCheck("Inside move Object");

/*    static double xValue = 0.0;
    static double yValue = 0.0;
    static double zValue = 0.0; */

    if(translationVector == -1)
    {
        std::cerr << "INVALID Shader or Uniform name ::INSIDE moveObject::" << std::endl;
        return;
    }

    glm::mat4 newMatrix;

    switch (axis)
    {
        case 'X':
		newMatrix = shapeToTransform.getTransformationMatrix();
		newMatrix[3][0] += moveAmount;
		shapeToTransform.setTransformationMatrix(newMatrix, vertexShaderId);
            break;
 	case 'Y':    
		newMatrix = shapeToTransform.getTransformationMatrix();
		newMatrix[3][1] += moveAmount;
		shapeToTransform.setTransformationMatrix(newMatrix, vertexShaderId);
	    break;
    
        case 'Z': 
		newMatrix = shapeToTransform.getTransformationMatrix();
		newMatrix[3][2] += moveAmount;
		shapeToTransform.setTransformationMatrix(newMatrix, vertexShaderId);
	    break;
    
        default:
        break;
    }

	
}
