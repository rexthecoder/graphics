#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Frame call back that would allow us to resize our window
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Function that would allow us to process input from the keyboard
void processInput(GLFWwindow *window);

// Shader sources
const GLchar *vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    out vec3 Color;
    void main()
    {
        Color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar *fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    out vec4 outColor;
    void main()
    {
        outColor = vec4(Color, 1.0);
    }
)glsl";

int main()
{
    // Initialize and configure GLFW
    glfwInit();
    // Allow us to specify the heighest version of openGl we want to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // Allow us to specify the lowest version of openGl we want to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Allow us to specify the profile we want to use [Either Compat profile  or Core Profile]
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a window object
    GLFWwindow *window = glfwCreateWindow(800, 600, "Example04", NULL, NULL);

    // Check if the window was created successfully
    // if not then the program is terminated
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW windows" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the context of the window the main context on the current thread
    glfwMakeContextCurrent(window);
    // Set the frame call back function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //  check if all the GLAD has Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    GLfloat vertices[] = {
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f // Bottom-left
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0};

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// Function that would allow us to resize our window
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Function that would allow us to process input from the keyboard
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
