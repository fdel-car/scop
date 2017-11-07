/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:39:24 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/07 17:57:32 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const GLchar	*vertex_shader_source = "#version 410 core\n"
    "in vec3 vertices;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(vertices, 1.0);\n"
    "}\0";

const GLchar	*frag_shader_source = "#version 410 core\n"
    "out vec4 frag_color;\n"
    "void main()\n"
    "{\n"
    "frag_color = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
    "}\0";

GLfloat init_shaders(void)
{
    GLfloat shader_program;
    GLuint vertex_shader;
    GLuint frag_shader;
    GLchar info_log[512];
    GLint success;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        ft_putendl("ERROR::SHADER::VERTEX: Compilation failed\n");
        ft_putendl(info_log);
    }
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_source, NULL);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag_shader, 512, NULL, info_log);
        ft_putendl("ERROR::SHADER::FRAGMENT: Compilation failed\n");
        ft_putendl(info_log);
    }
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        ft_putendl("ERROR::SHADER::PROGRAM: Linking failed\n");
        ft_putendl(info_log);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);
    return (shader_program);
}
