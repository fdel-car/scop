/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:39:24 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 12:47:19 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const	GLchar	*g_vertex_shader_source = "#version 410 core\n"
"layout (location = 0) in vec3 vertices;\n"
"layout (location = 1) in vec2 textures;\n"
"layout (location = 2) in vec3 normals;\n"
"layout (location = 3) in vec3 colors;\n"
"layout (location = 4) in float tex_indice;\n"
"out vec3 data_vertices;\n"
"out vec2 textures_coords;\n"
"out vec3 data_normals;\n"
"out vec3 data_colors;\n"
"out float indice;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position = projection * view * model * vec4(vertices, 1.0)\
+ vec4(normals * 0.0001, 1.0);\n"
"data_vertices = vec3(model * vec4(vertices, 1.0f)) + vec3(normals * 0.0001);\n"
"textures_coords = textures;\n"
"data_normals = normals;\n"
"data_colors = colors;\n"
"indice = tex_indice;\n"
"}\0";

const	GLchar	*g_frag_shader_source = "#version 410 core\n"
"out vec4 color;\n"
"in vec3 data_vertices;\n"
"in vec2 textures_coords;\n"
"in vec3 data_normals;\n"
"in vec3 data_colors;\n"
"in float indice;\n"
"uniform mat4 model;\n"
"uniform struct s_light {\n"
"vec3 position;\n"
"vec3 color;\n"
"} t_light;\n"
"uniform sampler2D obj_texture[16];\n"
"uniform float coeff_texture;\n"
"void main()\n"
"{\n"
"int tex_indice = int(indice);\n"
"vec4 color_frag = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"if (tex_indice >= 0) {\n"
"color_frag = texture(obj_texture[tex_indice], textures_coords);\n"
"}\n"
"float ambient_strength = 0.25f;\n"
"vec3 ambient_color = ambient_strength * t_light.color;\n"
"vec3 norm = normalize(data_normals);\n"
"vec3 light_dir = normalize(t_light.position * mat3(model) - data_vertices);\n"
"float diff = dot(norm, light_dir);\n"
"if (diff < 0) {\n"
"diff *= -1;\n"
"}\n"
"diff = max(diff, 0.0);\n"
"vec3 diffuse = diff * t_light.color;\n"
"vec3 result = (ambient_color + diffuse) * (data_colors *\
(1.0f - coeff_texture)) + (ambient_color + diffuse) * (vec3(color_frag.xyz)\
* (coeff_texture));\n"
"if (tex_indice < 0)\n"
"result = (ambient_color + diffuse) * data_colors;\n"
"color = vec4(result, 1.0f);\n"
"}\0";

void				log_shaders(GLint shader)
{
	GLint			success;
	GLchar			info_log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		printf("ERROR::SHADER::VERTEX: Compilation failed\n");
		printf("%s\n", info_log);
	}
}

void				init_shaders(void)
{
	GLuint			vertex_shader;
	GLuint			frag_shader;
	GLint			success;
	GLchar			info_log[512];

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &g_vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	log_shaders(vertex_shader);
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &g_frag_shader_source, NULL);
	glCompileShader(frag_shader);
	log_shaders(frag_shader);
	g_env.shader_program = glCreateProgram();
	glAttachShader(g_env.shader_program, vertex_shader);
	glAttachShader(g_env.shader_program, frag_shader);
	glLinkProgram(g_env.shader_program);
	glGetProgramiv(g_env.shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(g_env.shader_program, 512, NULL, info_log);
		printf("ERROR::SHADER::PROGRAM: Linking failed\n%s\n", info_log);
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
}

void				get_version(GLFWwindow *window)
{
	int				width;
	int				height;
	const GLubyte	*renderer = glGetString(GL_RENDERER);
	const GLubyte	*version = glGetString(GL_VERSION);

	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);
}
