/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:35:36 by fdel-car          #+#    #+#             */
/*   Updated: 2018/08/07 13:24:55 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void			free_tab(char **tab, int iter)
{
	while (tab[iter])
		free(tab[iter++]);
	free(tab);
}

void			init_env(void)
{
	int iter;

	g_env.c_pos = vec_new(0, 0, 0);
	g_env.up = vec_new(0, 1, 0);
	g_env.front = vec_new(0, 0, -1);
	iter = 0;
	while (iter < 1024)
		g_env.input[iter++] = 0;
	g_env.initialized = 0;
	g_env.last_x = WIDTH / 2;
	g_env.last_y = HEIGHT / 2;
	g_env.fov = 45.0f;
	g_env.yaw = -90.0f;
	g_env.pitch = 0.0f;
	g_env.rot_x = 0.0f;
	g_env.rot_y = 0.0f;
	g_env.textured = 0;
	g_env.coeff_texture = 0.0f;
}

void			change_coeff_texture(void)
{
	if (g_env.textured == 1 && g_env.coeff_texture < 1.0f)
		g_env.coeff_texture += 1.0f * g_env.delta_time;
	else if (g_env.textured == 0 && g_env.coeff_texture > 0.0f)
		g_env.coeff_texture -= 1.0f * g_env.delta_time;
	glUniform1f(glGetUniformLocation(g_env.shader_program, "coeff_texture"),
	g_env.coeff_texture);
}

GLFWwindow		*init_window(void)
{
	GLFWwindow *window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(WIDTH, HEIGHT, "scop_2.0", NULL, NULL);
	if (!window)
	{
		ft_putstr("ERROR: Could not open window with GLFW3\n");
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	return (window);
}

int				main(int ac, char **av)
{
	GLFWwindow	*window;

	init_env();
	if (!glfwInit())
	{
		ft_putstr("ERROR: Could not start GLFW3\n");
		return (-1);
	}
	window = init_window();
	if (!window)
		return (-1);
	glewExperimental = GL_TRUE;
	glewInit();
	get_version(window);
	init_shaders();
	if (ac != 2)
	{
		ft_putstr("ERROR: Obj missing in command line\n");
		glfwTerminate();
		return (-1);
	}
	return (unload_main(window, av));
}
