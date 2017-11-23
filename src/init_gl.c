/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:39:24 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/23 19:11:19 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const GLchar	*vertex_shader_source = "#version 410 core\n"
    "layout (location = 0) in vec3 vertices;\n"
	"layout (location = 1) in vec2 textures;\n"
	"layout (location = 2) in vec3 normals;\n"
	"out vec3 data_vertices;\n"
	"out vec3 data_normals;\n"
	"uniform mat4 model;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view * model * vec4(vertices, 1.0);\n"
	"data_vertices = vec3(model * vec4(vertices, 1.0f));\n"
	"data_normals = normals;\n"
    "}\0";

const GLchar	*frag_shader_source = "#version 410 core\n"
	"out vec4 color;\n"
	"in vec3 data_vertices;\n"
	"in vec3 data_normals;\n"
    "uniform mat4 model;\n"
    "uniform struct s_light {\n"
       "vec3 position;\n"
       "vec3 color;\n"
    "} t_light;\n"
	"uniform vec3 obj_color;\n"
    "void main()\n"
    "{\n"
	"float ambient_strength = 0.15f;\n"
	"vec3 ambient_color = ambient_strength * t_light.color;\n"
	"vec3 norm = normalize(data_normals);\n"
	"vec3 light_dir = normalize(t_light.position * mat3(model) - data_vertices);\n"
	"float diff = max(dot(norm, light_dir), 0.0);\n"
	"vec3 diffuse = diff * t_light.color;\n"
	"vec3 result = (ambient_color + diffuse) * obj_color;\n"
	"color = vec4(result, 1.0f);\n"
    "}\0";

GLuint init_shaders(void)
{
    GLuint shader_program;
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
