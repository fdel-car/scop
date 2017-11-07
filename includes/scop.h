/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:28:24 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/07 20:26:28 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define WIDTH 1920
# define HEIGHT 1080
# define START_SIZE 8192

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

typedef	struct		s_obj {
	GLfloat			*vertices;
	GLfloat			*data;
	GLint			nb_vertices;
	GLint			size_vertices;
	GLint			size_data;
	GLint			data_index;
}					t_obj;

t_obj	*load_obj(char *str);
GLfloat	init_shaders(void);
