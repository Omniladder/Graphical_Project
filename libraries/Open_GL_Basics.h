#ifndef First_Library
#define First_Library

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "thirdParty/glfw3.h" //Graphical usage


void ClearErrors() { //Removes all stored Errors that have been stored
    while (glGetError() != GL_NO_ERROR) {}
}

void errorCheck(const std::string& location) { //Checks to see if any errors has happens and then outputs the error and the location it happened

    	GLenum error;

	while (( error = glGetError()) != 0) //Checks if an error has occurred
	{
        std::cerr << "OpenGL Error at " << location << ": "; //Gives User error location
        switch (error) { //gives the user the error that has happened
            case GL_INVALID_ENUM:
                std::cerr << "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL_OUT_OF_MEMORY";
                break;
            default:
                std::cerr << "Unknown error code: " << error;
                break;
    }
        std::cerr << std::endl << std::endl; 
	}
}

void PreCode(GLFWwindow* window, GLuint shader) //Everything at the start of the main loop
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT); // Empties out the color buffer

    int width, height; //Stores the window size
    glfwGetWindowSize(window, &width, &height); //retrives the windows size
    glViewport(0, 0, width, height); //Sets the windoes coordinate System


}

bool PostCode(GLFWwindow* window) //Everything that goes at the end of the main loop
{
    // Swap buffers and poll events
    glfwSwapBuffers(window); //Swaps the newly drawn window with the previously shown window
    glfwPollEvents(); //Checks if anything important has happened since last run
    if(glfwWindowShouldClose(window)) //checks wheter user attempted to close window if so it closes the window needs to go at the end of the code to test every run
    {
        glfwTerminate();
        return false;
    }
    else
    {
        return true;
    }
}


GLFWwindow* openWindow(int windows_width, int windows_height, const char* windows_title) //creates the window
{
    if (!glfwInit()) //Tests if the wranglet library properly intilazied
    {
        printf("::GLFW FAILED TO INTIALIZE PLEASE RETRY:: \n");
        return nullptr; // GLFW initialization failed
    }

    GLFWwindow* window = glfwCreateWindow(windows_width, windows_height, windows_title, nullptr, nullptr); //Makes the window
    if (!window) //Tests if the window properly opened
    {
        glfwTerminate(); //Closes GLFW
        printf("::WINDOW FAILED TO OPEN PLEASE RETRY:: \n");
        return nullptr; // Window creation failed
    }

    glfwMakeContextCurrent(window); //Sets this window as the wndow to use
    glewInit(); //Intializes GLEW

    errorCheck("INSIDE Open_window");
    return window;
}

void closeWindow(unsigned int Shader_ID, unsigned int Buffer_ID)
{
    glDeleteBuffers(1, &Buffer_ID); 
    glDeleteProgram(Shader_ID); //Cleans up the program
    glfwTerminate();
}


//TODO #3 COMMENT AFTER HERE

static unsigned int compileShader(const std::string source, GLuint type)
{
    GLuint id = glCreateShader(type);
    const char* src = source.c_str(); // turns source into char array
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        printf("COMPILER FAILED\n");
        printf("%s\n", message);
    }

    return id;
}

static GLuint createShader(const std::string& vertexShader, const std::string& fragmentShader, GLuint& vID, GLuint&  fID)
{
    GLuint programId = glCreateProgram();
    GLuint vertexShaderID = compileShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fragShaderID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(programId, vertexShaderID);
    glAttachShader(programId, fragShaderID);
    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragShaderID);

    return programId;
}


std::string readInFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return "";
    }

    std::string data; // Corrected to std::stringstream
    data.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); //Turns ifstream into string idk how

    return data;
}


unsigned int activateShaders(std::string verShader, std::string fragmentationShader, GLuint& vID, GLuint& fID)//enter file location of vertex and fragShader
{
    std::string vertexShader = readInFile(verShader);
    unsigned int shader;
    std::string fragmentShader = readInFile(fragmentationShader);
    shader = createShader(vertexShader,fragmentShader, vID, fID);
    
    glUseProgram(shader);
    return shader;
}

void Runtime_Reloading(GLFWwindow* window, unsigned int &shader, int key, const std::string& vertexShader, const std::string& fragmentShader, GLuint& vID, GLuint& fID ) { //reloads the GPU when button has been pressed
    
    if (glfwGetKey(window, key) == GLFW_PRESS) { //tests if button has been pressed
        shader = activateShaders(vertexShader, fragmentShader, vID, fID); //reloads the shader
    }
}


#endif
