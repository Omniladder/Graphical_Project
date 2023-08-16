#ifndef First_Library
#define First_Library

#include <cmath>    // for trigonometry functions
#include <math.h>
#include <string>
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage

void PreCode(GLFWwindow* window)
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

GLFWwindow* Open_window(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        return nullptr; // GLFW initialization failed
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return nullptr; // Window creation failed
    }

    glfwMakeContextCurrent(window);
    glewInit();

    return window;
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

static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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


unsigned int activateShaders(std::string verShader, std::string fragmentationShader)//enter file location of vertex and fragShader
{
    std::string vertexShader = readInFile(verShader);
    unsigned int shader;
    std::string fragmentShader = readInFile(fragmentationShader);
    shader = CreateShader(vertexShader,fragmentShader);
    
    glUseProgram(shader);
    return shader;
}



#endif