#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Frame call back that would allow us to resize our window
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Function that would allow us to process input from the keyboard
void processInput(GLFWwindow *window);

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
    GLFWwindow *window = glfwCreateWindow(800, 600, "Rexford Asamoah", NULL, NULL);

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
   
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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