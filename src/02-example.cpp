

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Specifying our version of the GLSL [3.3]
// After we specify that we are using core profile 


// Our ver vertixes shader to use in our application
const char *vertexShaderSource = "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

/// Fragment shader is about calculating the color output of pixels
const char *framgmentShaderSource = "#version 330 core\n"
       "out vec4 FragColor;\n"
       "void main()\n"
       "{\n"
       "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
       "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Rexford Asamoah", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW windows" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" <<
                   infoLog << std::endl;
                
    }

    //fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &framgmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    

}


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}