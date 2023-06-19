#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"

#include "gl_util.h"

#define MAX_LOG_LENGTH 1024

const GLchar*
load_shader_source(const char* filename) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "[error] Failed to open '%s'!", filename);
        return NULL;
    }

    // Get the size of the file.
    fseek(fp, 0L, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    // Read file into char*
    char* source = malloc(file_size * (sizeof(char) + 1));
    for (int i = 0; i < file_size; i++) {
        source[i] = fgetc(fp);
    }
    source[file_size] = '\0';

    fclose(fp);
    return (const GLchar*) source;
}

GLuint 
create_shader_program(
    const char* vertex_filepath, 
    const char* fragment_filepath
) {
    GLint success;

    // Vertex shader
    const GLchar* vertex_shader_source = load_shader_source(vertex_filepath);
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    free((void*) vertex_shader_source);

    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLchar log[MAX_LOG_LENGTH];
        glGetShaderInfoLog(vertex_shader, MAX_LOG_LENGTH, NULL, log);
        fprintf(stderr, "[error] Error while compiling vertex shader:\n%s", log);
        return 0;
    }

    // Fragment shader
    const GLchar* fragment_shader_source = load_shader_source(fragment_filepath);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    free((void*) fragment_shader_source);

    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLchar log[MAX_LOG_LENGTH];
        glGetShaderInfoLog(fragment_shader, MAX_LOG_LENGTH, NULL, log);
        fprintf(stderr, "[error] Error while compiling fragment shader:\n%s", log);
        return 0;
    }

    // Programme~
    GLuint shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {
        GLchar log[MAX_LOG_LENGTH];
        glGetProgramInfoLog(shader_program, MAX_LOG_LENGTH, NULL, log);
        fprintf(stderr, "[error] Error while linking shader program:\n%s", log);
        return 0;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}