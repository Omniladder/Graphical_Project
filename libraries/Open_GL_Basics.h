#ifndef First_Library
#define First_Library

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "glfw3.h" //Graphical usage

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data)
{
    const char* _source;
    const char* _type;
    const char* _severity;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

        case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

        case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

        default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

        case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

        case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

        case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

        default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

        case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

        default:
        _severity = "UNKNOWN";
        break;
    }

    printf(" OPENGL NOTIFICATION :: %d: %s of %s severity, raised from %s: %s\n", id, _type, _severity, _source, msg);
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

    glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLDebugMessageCallback, nullptr);

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
