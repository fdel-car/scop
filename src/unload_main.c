/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:32:03 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/30 18:36:47 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		init_buffer_data(t_obj *obj)
{
	glGenVertexArrays(1, &g_env.vao_obj);
	glGenBuffers(1, &g_env.vbo_obj);
	glBindVertexArray(g_env.vao_obj);
	glBindBuffer(GL_ARRAY_BUFFER, g_env.vbo_obj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * obj->data_index *\
	DATA_SIZE, obj->data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, DATA_SIZE *\
	sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, DATA_SIZE *\
	sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, DATA_SIZE *\
	sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, DATA_SIZE *\
	sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, DATA_SIZE *\
	sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void		init_uniforms(void)
{
	GLint	light_pos_loc;
	GLint	light_color_loc;

	light_pos_loc = glGetUniformLocation(g_env.shader_program,\
	"t_light.position");
	light_color_loc = glGetUniformLocation(g_env.shader_program,\
	"t_light.color");
	glUniform3f(light_pos_loc, g_env.c_pos.x, g_env.c_pos.y, g_env.c_pos.z);
	glUniform3f(light_color_loc, 1.0f, 1.0f, 1.0f);
	g_env.projection_loc = glGetUniformLocation(g_env.shader_program,\
	"projection");
	g_env.view_location = glGetUniformLocation(g_env.shader_program, "view");
	g_env.model_location = glGetUniformLocation(g_env.shader_program, "model");
}

void		free_all(GLFWwindow *window)
{
	free(g_env.projection);
	free(g_env.rotate_x);
	free(g_env.rotate_y);
	free(g_env.model_obj);
	free(g_env.view);
	glBindVertexArray(0);
	glfwSwapBuffers(window);
	ft_printf("FPS : %d \r", (int)(1.0f / (g_env.delta_time)));
}

void		main_loop(GLFWwindow *window, t_obj *obj)
{
	while (!glfwWindowShouldClose(window))
	{
		g_env.frame = glfwGetTime();
		g_env.delta_time = g_env.frame - g_env.last_frame;
		g_env.last_frame = g_env.frame;
		glfwPollEvents();
		use_key();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUniform1i(glGetUniformLocation(g_env.shader_program, "is_textured"),
		g_env.textured);
		g_env.view = look_at4x4(g_env.c_pos, vec_add(g_env.c_pos,
		g_env.front), g_env.up);
		g_env.projection = perspective_projection(g_env.fov,
		(float)WIDTH / (float)HEIGHT, 0.1f, obj->range);
		glUniformMatrix4fv(g_env.projection_loc, 1, GL_FALSE, g_env.projection);
		glBindVertexArray(g_env.vao_obj);
		glUniformMatrix4fv(g_env.view_location, 1, GL_FALSE, g_env.view);
		g_env.rotate_x = rotate4x4_x(g_env.rot_x);
		g_env.rotate_y = rotate4x4_y(g_env.rot_y);
		g_env.model_obj = mult_matrice4x4(g_env.rotate_x, g_env.rotate_y);
		glUniformMatrix4fv(g_env.model_location, 1, GL_FALSE, g_env.model_obj);
		glDrawArrays(GL_TRIANGLES, 0, obj->data_index * 3);
		free_all(window);
	}
}

int			unload_main(GLFWwindow *window, char **av)
{
	t_obj	*obj;

	obj = load_obj(av[1]);
	if (obj == NULL)
	{
		ft_printf("ERROR: Obj not parsed correctly, try to import and\
		export it with Blender\n");
		glfwTerminate();
		return (-1);
	}
	init_buffer_data(obj);
	glUseProgram(g_env.shader_program);
	init_uniforms();
	if (g_env.textured)
		set_texture(obj);
	main_loop(window, obj);
	glDeleteVertexArrays(1, &g_env.vao_obj);
	glDeleteBuffers(1, &g_env.vbo_obj);
	glfwTerminate();
	free(obj);
	return (0);
}
