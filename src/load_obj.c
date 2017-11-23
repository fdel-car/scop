/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:59:30 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/23 17:45:25 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	throw_error(char *error)
{
	ft_putstr("ERROR:");
	ft_putendl(error);
	exit(0);
}

void	load_vertices(char *line, t_obj *obj)
{
	char **tab;

	tab = ft_strsplit(line, ' ');
	int iter = 0;
	while (tab[iter])
		iter++;
	if (iter > 4)
		throw_error(":PARSER: Wrong vertices line format in .obj");
	obj->nb_vertices += 3;
	while (obj->nb_vertices > obj->size_vertices)
	{
		ft_putendl("Not enough size in vertices, reallocing...");
		obj->size_vertices *= 2;
		obj->vertices = (GLfloat *)realloc(obj->vertices, sizeof(GLfloat) * obj->size_vertices);
		if (!obj->vertices) {
			throw_error(":MEMORY: Malloc error, the vertices array is probably getting too large.");
		}
	}
	obj->vertices[obj->nb_vertices - 3] = ft_atof(tab[1]) - obj->half_width;
	obj->vertices[obj->nb_vertices - 2] = ft_atof(tab[2]) - obj->half_height;
	obj->vertices[obj->nb_vertices - 1] = ft_atof(tab[3]) - obj->half_depth;
	iter = 0;
	while (tab[iter])
		free(tab[iter++]);
	free(tab);
}

void	load_textures(char *line, t_obj *obj)
{
	char **tab;

	tab = ft_strsplit(line, ' ');
	int iter = 0;
	while (tab[iter])
		iter++;
	if (iter > 3)
		throw_error(":PARSER: Wrong texture coordinates line format in .obj");
	obj->nb_textures += 2;
	while (obj->nb_textures > obj->size_textures)
	{
		ft_putendl("Not enough size in textures, reallocing...");
		obj->size_textures *= 2;
		obj->textures = (GLfloat *)realloc(obj->textures, sizeof(GLfloat) * obj->size_textures);
		if (!obj->textures) {
			throw_error(":MEMORY: Malloc error, the texture coordinates array is probably getting too large.");
		}
	}
	obj->textures[obj->nb_textures - 2] = ft_atof(tab[1]);
	obj->textures[obj->nb_textures - 1] = ft_atof(tab[2]);
	iter = 0;
	while (tab[iter])
		free(tab[iter++]);
	free(tab);
}

void	load_normals(char *line, t_obj *obj)
{
	char **tab;

	tab = ft_strsplit(line, ' ');
	int iter = 0;
	while (tab[iter])
		iter++;
	if (iter > 4)
		throw_error(":PARSER: Wrong normals line format in .obj");
	obj->nb_normals += 3;
	while (obj->nb_normals > obj->size_normals)
	{
		ft_putendl("Not enough size in normals, reallocing...");
		obj->size_normals *= 2;
		obj->normals = (GLfloat *)realloc(obj->normals, sizeof(GLfloat) * obj->size_normals);
		if (!obj->normals) {
			throw_error(":MEMORY: Malloc error, the normals array is probably getting too large.");
		}
	}
	obj->normals[obj->nb_normals - 3] = ft_atof(tab[1]);
	obj->normals[obj->nb_normals - 2] = ft_atof(tab[2]);
	obj->normals[obj->nb_normals - 1] = ft_atof(tab[3]);
	iter = 0;
	while (tab[iter])
		free(tab[iter++]);
	free(tab);
}

void	load_data_vertices(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * DATA_SIZE] = obj->vertices[index * 3];
	obj->data[obj->data_index * DATA_SIZE + 1] = obj->vertices[index * 3 + 1];
	obj->data[obj->data_index * DATA_SIZE + 2] = obj->vertices[index * 3 + 2];
}

void	load_data_textures(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * DATA_SIZE + 3] = obj->textures[index * 2];
	obj->data[obj->data_index * DATA_SIZE + 4] = obj->textures[index * 2 + 1];
}

void	load_data_normals(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * DATA_SIZE + 5] = obj->normals[index * 3];
	obj->data[obj->data_index * DATA_SIZE + 6] = obj->normals[index * 3 + 1];
	obj->data[obj->data_index * DATA_SIZE + 7] = obj->normals[index * 3 + 2];
}

void	load_data(char *line, t_obj *obj)
{
	char	**tab;
	char	**each;
	int		tmp;

	tab = ft_strsplit(line, ' ');
	int iter = 0;
	while (tab[iter])
		iter++;
	if (iter == 4)
	{
		iter = 1;
		while (iter < 4)
		{
			while ((obj->data_index + 1) * DATA_SIZE > obj->size_data)
			{
				ft_putendl("Not enough size in data array, reallocing...");
				obj->size_data *= 2;
				obj->data = (GLfloat *)realloc(obj->data, sizeof(GLfloat) * obj->size_data);
				if (!obj->data) {
					throw_error(":MEMORY: Malloc error, the data array is probably getting too large.");
				}
			}
			tmp = 0;
			each = ft_strsplit(tab[iter], '/');
			if (each[tmp] && obj->nb_vertices)
				load_data_vertices(obj, ft_atoi(each[tmp++]) - 1);
			if (each[tmp] && obj->nb_textures)
				load_data_textures(obj, ft_atoi(each[tmp++]) - 1);
			if (each[tmp] && obj->nb_normals)
				load_data_normals(obj, ft_atoi(each[tmp++]) - 1);
			tmp = 0;
			while (each[tmp])
				free(each[tmp++]);
			free(each);
			obj->data_index++;
			iter++;
		}
	} else {
		throw_error(":PARSER: Triangulate the .obj before running again the program, use Blender for instance.");
	}
	iter = 0;
	while (tab[iter])
		free(tab[iter++]);
	free(tab);
}

void	pre_compute_data(char *path, t_obj *obj)
{
	int		fd;
	float	tmp;
	char	*line;
	char	**tab;

	if ((fd = open(path, O_RDONLY)) < 0)
		return ;
	obj->min_x = INT_MAX;
	obj->min_y = INT_MAX;
	obj->min_z = INT_MAX;
	obj->max_x = INT_MIN;
	obj->max_y = INT_MIN;
	obj->max_z = INT_MIN;
	obj->range = 0;
	obj->nb_vertices = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' & line[1] == ' ')
		{
			tab = ft_strsplit(line, ' ');
			tmp = ft_atof(tab[1]);
			if (tmp < obj->min_x)
				obj->min_x = tmp;
			if (tmp > obj->max_x)
				obj->max_x = tmp;
			tmp = ft_atof(tab[2]);
			if (tmp < obj->min_y)
				obj->min_y = tmp;
			if (tmp > obj->max_y)
				obj->max_y = tmp;
			tmp = ft_atof(tab[3]);
			if (tmp < obj->min_z)
				obj->min_z = tmp;
			if (tmp > obj->max_z)
				obj->max_z = tmp;
			int iter = 0;
			while (tab[iter])
				free(tab[iter++]);
			free(tab);
			obj->nb_vertices++;
		}
		free(line);
	}
	free(line);
	obj->half_width = (obj->min_x + obj->max_x) / 2;
	obj->half_height = (obj->min_y + obj->max_y) / 2;
	obj->half_depth = (obj->min_z + obj->max_z) / 2;
	if (fabs(obj->min_x) + fabs(obj->max_x) > obj->range)
	obj->range = fabs(obj->min_x) + fabs(obj->max_x);
	if (fabs(obj->min_y) + fabs(obj->max_y) > obj->range)
	obj->range = fabs(obj->min_y) + fabs(obj->max_y);
	if (fabs(obj->min_z) + fabs(obj->max_z) > obj->range)
	obj->range = fabs(obj->min_z) + fabs(obj->max_z);
	close(fd);
	g_env.c_pos.z += 1.0f * obj->range;
}

t_obj	*load_obj(char *path)
{
	char	*line;
	int     fd;
	t_obj   *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	pre_compute_data(path, obj);
	obj->vertices = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->textures = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->normals = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->data = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->size_vertices = START_SIZE;
	obj->size_textures = START_SIZE;
	obj->size_normals = START_SIZE;
	obj->size_data = START_SIZE;
	obj->nb_vertices = 0;
	obj->nb_textures = 0;
	obj->nb_normals = 0;
	obj->data_index = 0;
	if (!obj || !obj->vertices || !obj->data) {
		return NULL;
	}
	if ((fd = open(path, O_RDONLY)) < 0)
	{
		free(obj);
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
			load_vertices(line, obj);
		if (line[0] == 'v' && line[1] == 't')
			load_textures(line, obj);
		if (line[0] == 'v' && line[1] == 'n')
			load_normals(line, obj);
		if (line[0] == 'f' && line[1] == ' ')
			load_data(line, obj);
		free(line);
	}
	free(line);
	close(fd);
	printf("This .obj has %d vertices.\n", obj->nb_vertices / 3);
	printf("This .obj has %d textures coordinates.\n", obj->nb_textures / 2);
	printf("This .obj has %d normals.\n", obj->nb_normals / 3);
	printf("This .obj has %d triangles.\n", obj->data_index / 3);
	return (obj);
}
