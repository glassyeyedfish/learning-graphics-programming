#include <stdbool.h>
#include <stdio.h>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

void
load_shader_source(const char* filename) {
    FILE* f = fopen(filename, "r");


    fclose(f);
}

void 
framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}

void
main_input(GLFWwindow* window) 
{
    glfwPollEvents();    

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void
main_update(GLFWwindow* window) 
{
    /*
     * Here we set up the data that will be passed to the GPU.
     */
    float vertex_data[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.f
    };

    /*
     * Here we set up a "vertex buffer object". It is a region of memory in the 
     * GPU that we can write our vertex data to.
     */

    // The unique ID of the VBO.
    GLuint vbo;

    // Assigning the ID to the VBO.
    glGenBuffers(1, &vbo);

    // Setting the type of VBO.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Writing the vertex data to the VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
}

void
main_render(GLFWwindow* window)
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

int 
main() 
{
    /* Boilerplate */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Window / Context Setup */
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "[fatal] Failed to create GLFW window!");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "[fatal] Failed to initialize GLAD!");
        return -1;
    }  

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Main Loop */
    while (!glfwWindowShouldClose(window)) {
        main_input(window);
        main_update(window);
        main_render(window);
    }

    glfwTerminate();
    return 0;
} 