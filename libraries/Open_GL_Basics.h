#ifndef First_Library
#define First_Library

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage


void ClearErrors() {
    while (glGetError() != GL_NO_ERROR) {}
}

void errorCheck(const std::string& location) {

    	GLenum error;

	while (( error = glGetError()) != 0)
	{
        std::cerr << "OpenGL Error at " << location << ": ";
        switch (error) {
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
        std::cout << std::endl;
        std::cout << std::endl;
    }
	}
}

void PreCode(GLFWwindow* window, GLuint shader)
{
    // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        int width, height;
        // Set the viewport size to match the window size
        glfwGetWindowSize(window, &width, &height);
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);


}

bool PostCode(GLFWwindow* window)
{
    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
    if(glfwWindowShouldClose(window))
    {
        glfwTerminate();
        return false;
    }
    else
    {
        return true;
    }
}


GLFWwindow* Open_window(int windows_width, int windows_height, const char* windows_title)
{
    if (!glfwInit())
    {
        std::cout<<"::GLFW FAILED TO INTIALIZE PLEASE RETRY::"<<std::endl;
        return nullptr; // GLFW initialization failed
    }

    GLFWwindow* window = glfwCreateWindow(windows_width, windows_height, windows_title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cout<<"::WINDOW FAILED TO OPEN PLEASE RETRY::"<<std::endl;
        return nullptr; // Window creation failed
    }

    glfwMakeContextCurrent(window);
    glewInit();

errorCheck("INSIDE Open_window");
    return window;
}

void Close_Window(unsigned int Shader_ID, unsigned int Buffer_ID)
{
    glDeleteBuffers(1, &Buffer_ID);
    glDeleteProgram(Shader_ID);
    glfwTerminate();
}


static unsigned int CompileShader(const std::string source, GLuint type)
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
        std::cout << "Compiler Failed" << std::endl;
        std::cout << message << std::endl;
    }

    return id;
}

static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader, GLuint& vID, GLuint&  fID)
{
    GLuint programId = glCreateProgram();
    GLuint vertexShaderID = CompileShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fragShaderID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

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
    shader = CreateShader(vertexShader,fragmentShader, vID, fID);
    
    glUseProgram(shader);
    return shader;
}

void Runtime_Reloading(GLFWwindow* window, unsigned int &shader, int key, const std::string& vertexShader, const std::string& fragmentShader, GLuint& vID, GLuint& fID ) {
    
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        shader = activateShaders(vertexShader, fragmentShader, vID, fID);
    }
}


#endif
