#include <fstream>
#include "Shapes.h"
#include <string>
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
	ClearErrors();
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

	glm::mat4 translationMatrix(1.0);

	translationMatrix[3][0] = xValue;
	translationMatrix[3][1] = yValue;
	translationMatrix[3][2] = zValue;

    glUniformMatrix4fv(translationVector, 1, GL_FALSE, &translationMatrix[0][0]);
	errorCheck("Bottom of Move Object");
}
