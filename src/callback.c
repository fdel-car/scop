/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:38:39 by fdel-car          #+#    #+#             */
/*   Updated: 2017/12/06 16:31:40 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	move_camera(void)
{
	t_vec3 front;

	front.x = cos(g_env.yaw * M_PI / 180) * cos(g_env.pitch * M_PI / 180);
	front.y = sin(g_env.pitch * M_PI / 180);
	front.z = sin(g_env.yaw * M_PI / 180) * cos(g_env.pitch * M_PI / 180);
	g_env.front = vec_norm(front);
}

void	use_key(void)
{
	if (g_env.input[GLFW_KEY_A])
	{
		g_env.yaw -= 0.25f * (g_env.fov / 15.0f);
		move_camera();
	}
	if (g_env.input[GLFW_KEY_D])
	{
		g_env.yaw += 0.25f * (g_env.fov / 15.0f);
		move_camera();
	}
	if (g_env.input[GLFW_KEY_W])
	{
		g_env.pitch += 0.25f * (g_env.fov / 15.0f);
		if (g_env.pitch > 89.0f)
			g_env.pitch = 89.0f;
		move_camera();
	}
	if (g_env.input[GLFW_KEY_S])
	{
		g_env.pitch -= 0.25f * (g_env.fov / 15.0f);
		if (g_env.pitch < -89.0f)
			g_env.pitch = -89.0f;
		move_camera();
	}
	change_coeff_texture();
}

void	scroll_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (ypos > 0)
		if (g_env.fov > 1.0f)
		{
			g_env.fov -= ypos * 0.5f;
			if (g_env.fov < 1.0f)
				g_env.fov = 1.0f;
		}
	if (ypos < 0)
		if (g_env.fov < 90.0f)
		{
			g_env.fov -= ypos * 0.5f;
			if (g_env.fov > 90.0f)
				g_env.fov = 90.0f;
		}
	(void)xpos;
	(void)window;
}

void	mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	GLfloat	sensitivity;
	GLfloat	xoffset;
	GLfloat	yoffset;

	if (g_env.initialized == 0)
	{
		g_env.last_x = xpos;
		g_env.last_y = ypos;
		g_env.initialized = 1;
	}
	xoffset = xpos - g_env.last_x;
	yoffset = g_env.last_y - ypos;
	g_env.last_x = xpos;
	g_env.last_y = ypos;
	sensitivity = 0.025f * (g_env.fov / 15.0f);
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	g_env.rot_y += xoffset;
	g_env.rot_x -= yoffset;
	(void)window;
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action,\
		int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
		g_env.input[key] = 1;
	else if (action == GLFW_RELEASE)
		g_env.input[key] = 0;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		if (g_env.textured)
		{
			g_env.textured = 0;
			ft_printf("Texture disabled.\n");
		}
		else if (!g_env.textured)
		{
			g_env.textured = 1;
			ft_printf("Texture enabled.\n");
		}
	}
	(void)scancode;
	(void)mode;
}
