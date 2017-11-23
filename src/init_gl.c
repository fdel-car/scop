/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:39:24 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/23 17:50:57 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const GLchar	*vertex_shader_source = "#version 410 core\n"
    "layout (location = 0) in vec3 vertices;\n"
    "layout (location = 1) in vec2 textures;\n"
    "layout (location = 2) in vec3 normals;\n"
    "out vec3 data_normals;\n"
    "out vec3 data_vertices;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "void main()\n"
    "{\n"
    "gl_Position = projection * view * model * vec4(vertices, 1.0);\n"
    "data_normals = normals;\n"
    "data_vertices = vertices;\n"
    "}\0";

const GLchar	*frag_shader_source = "#version 410 core\n"
    "out vec4 frag_color;\n"
    "in vec3 data_normals;\n"
    "in vec3 data_vertices;\n"
    "uniform mat4 model;\n"
    "uniform struct s_light {\n"
       "vec3 position;\n"
       "vec3 color;\n"
    "} t_light;\n"
    "uniform vec3 obj_color;\n"
    "void main()\n"
    "{\n"
    // Calculate normal in world coordinates
    "mat3 normal_matrix = transpose(inverse(mat3(model)));\n"
    "vec3 normal = normalize(normal_matrix * data_normals);\n"
    // Calculate the location of this fragment (pixel) in world coordinates
    "vec3 frag_position = vec3(model * vec4(data_vertices, 1));\n"
    // Calculate the vector from this pixels surface to the light source
    "vec3 surface_to_light = t_light.position - frag_position;\n"
    // Calculate the cosine of the angle of incidence
    "float brightness = dot(normal, surface_to_light) / (length(surface_to_light) * length(normal));\n"
    // "if (brightness < 0) {\n"
    //     "brightness *= -1;\n"
    // "}\n"
    "brightness = clamp(brightness, 0, 1);\n"
    "vec4 surface_color = vec4(obj_color, 1);\n"
    "frag_color = vec4(brightness * t_light.color * surface_color.xyz, surface_color.w);\n"
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
