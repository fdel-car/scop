/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:59:30 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/03 16:43:38 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		load_data_normals(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * DATA_SIZE + 5] = obj->normals[index * 3];
	obj->data[obj->data_index * DATA_SIZE + 6] = obj->normals[index * 3 + 1];
	obj->data[obj->data_index * DATA_SIZE + 7] = obj->normals[index * 3 + 2];
}

void		init_obj(char *path, t_obj *obj, int iter)
{
	int		l;

	obj->vertices = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->textures = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->normals = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->data = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE * 4);
	if (!obj->data || !obj->vertices || !obj->textures || !obj->normals)
		throw_error(":MEMORY: Malloc in obj data didn't work.");
	obj->size_vertices = START_SIZE;
	obj->size_textures = START_SIZE;
	obj->size_normals = START_SIZE;
	obj->size_data = START_SIZE * 4;
	obj->nb_vertices = 0;
	obj->nb_textures = 0;
	obj->nb_normals = 0;
	obj->data_index = 0;
	obj->current_color = vec_new(0.64f, 0.64f, 0.64f);
	l = ft_strlen(path);
	while ((l - 1) >= 0 && path[l - 1] != '/')
		l--;
	obj->path = ft_strndup(path, l);
	while (iter < 16)
		obj->sampler2d[iter++] = -1;
	obj->tex_indice = -1;
}

void		print_obj_data(t_obj *obj)
{
	ft_printf("This .obj has %d vertices.\n", obj->nb_vertices / 3);
	ft_printf("This .obj has %d textures coordinates.\n", obj->nb_textures / 2);
	if (obj->nb_normals)
		ft_printf("This .obj has %d normals.\n", obj->nb_normals / 3);
	else
		ft_putstr("This .obj did not have normals. They are generated on \
program start.\n");
	ft_printf("This .obj has %d triangles.\n", obj->data_index / 3);
	free(obj->path);
}

void		loop_parser(char *line, t_obj *obj, char *path)
{
	static float f = 1.0f;
	static float step = 1.0f;

	if (line[0] == 'v' && line[1] == ' ')
		load_vertices(line, obj);
	else if (line[0] == 'v' && line[1] == 't')
		load_textures(line, obj);
	else if (line[0] == 'v' && line[1] == 'n')
		load_normals(line, obj);
	else if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' &&
	line[3] == 'm' && line[4] == 't' && line[5] == 'l' && line[6] == ' ')
		load_material(line, obj, material_path(path));
	else if (line[0] == 'f' && line[1] == ' ')
	{
		if (!obj->use_mtl)
		{
			f += step;
			if (f + EPSILON >= 4.0f)
				step *= -1.0f;
			if (f - EPSILON <= 1.0f)
				step *= -1.0f;
			obj->current_color = vec_new(0.2f * f, 0.2f * f, 0.2f * f);
		}
		load_data(line, obj);
	}
}

t_obj		*load_obj(char *path)
{
	char	*line;
	int		fd;
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	pre_compute_data(path, obj);
	init_obj(path, obj, 0);
	if (!obj || !obj->vertices || !obj->data)
		return (NULL);
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		free(obj);
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		loop_parser(line, obj, path);
		free(line);
	}
	free(line);
	close(fd);
	if (obj->nb_normals == 0)
		init_normals(obj, 0);
	print_obj_data(obj);
	return (obj);
}
