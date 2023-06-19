#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

#include "gl_util.h"

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
        fprintf(stderr, "[error] Failed to create GLFW window!");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "[error] Failed to initialize GLAD!");
        return -1;
    }  

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Here we set up the data that will be passed to the GPU. */
    float vertex_data[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.f
    };

    /* Here we set up a "vertex buffer object". It is a region of memory in the 
     * GPU that we can write our vertex data to. */

    // The unique ID of the VBO.
    GLuint vbo;

    // Assigning the ID to the VBO.
    glGenBuffers(1, &vbo);

    // Setting the type of VBO.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Writing the vertex data to the VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    GLuint program = create_shader_program("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
    if (program == 0) {
        return -1;
    }

    /* Main Loop */
    while (!glfwWindowShouldClose(window)) {
        main_input(window);
        main_render(window);
    }

    glfwTerminate();
    return 0;
} 