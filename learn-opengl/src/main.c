#include <stdbool.h>
#include <stdio.h>

#include "glad/glad.h"

#include <GLFW/glfw3.h>

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
    // -- Nothing Yet --
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