/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:59:30 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/24 17:56:53 by fdel-car         ###   ########.fr       */
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
			obj->data[obj->data_index * DATA_SIZE + 8] = obj->current_color.x;
			obj->data[obj->data_index * DATA_SIZE + 9] = obj->current_color.y;
			obj->data[obj->data_index * DATA_SIZE + 10] = obj->current_color.z;
			tmp = 0;
			while (each[tmp])
				free(each[tmp++]);
			free(each);
			obj->data_index++;
			iter++;
		}
	} else if (iter == 5)
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
			obj->data[obj->data_index * DATA_SIZE + 8] = obj->current_color.x;
			obj->data[obj->data_index * DATA_SIZE + 9] = obj->current_color.y;
			obj->data[obj->data_index * DATA_SIZE + 10] = obj->current_color.z;
			tmp = 0;
			while (each[tmp])
				free(each[tmp++]);
			free(each);
			obj->data_index++;
			iter++;
		}
		iter = 3;
		while (iter != 2)
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
			obj->data[obj->data_index * DATA_SIZE + 8] = obj->current_color.x;
			obj->data[obj->data_index * DATA_SIZE + 9] = obj->current_color.y;
			obj->data[obj->data_index * DATA_SIZE + 10] = obj->current_color.z;
			tmp = 0;
			while (each[tmp])
				free(each[tmp++]);
			free(each);
			obj->data_index++;
			iter++;
			if (iter == 5)
				iter = 1;
		}
	} else if (iter > 5) {
		throw_error(":PARSER: The .obj has complex polygon with more than 4 sides.");
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

void	init_normals(t_obj *obj)
{
	int		tmp;
	int		iter;
	t_vec3	u[4];

	iter = 0;
	while (iter < obj->data_index)
	{
		u[0] = vec_new(obj->data[iter * DATA_SIZE],
		obj->data[iter * DATA_SIZE + 1], obj->data[iter * DATA_SIZE + 2]);
		iter++;
		u[1] = vec_new(obj->data[iter * DATA_SIZE],
		obj->data[iter * DATA_SIZE + 1], obj->data[iter * DATA_SIZE + 2]);
		iter++;
		u[2] = vec_new(obj->data[iter * DATA_SIZE],
		obj->data[iter * DATA_SIZE + 1], obj->data[iter * DATA_SIZE + 2]);
		iter++;
		u[3] = vec_norm(cross_product(vec_sub(u[0], u[1]),
		vec_sub(u[0], u[2])));
		tmp = 0;
		while (tmp < 3)
		{
			obj->data[(iter - 3) * DATA_SIZE + tmp * DATA_SIZE + 5] = u[3].x;
			obj->data[(iter - 3) * DATA_SIZE + tmp * DATA_SIZE + 6] = u[3].y;
			obj->data[(iter - 3) * DATA_SIZE + tmp * DATA_SIZE + 7] = u[3].z;
			tmp++;
		}
	}
}

int		load_material_data(char *use, char *new, int fd, t_obj *obj)
{
	char	**tmp;
	char	**each;
	char	*line;
	int     iter;

	iter = 0;
	tmp = ft_strsplit(new, ' ');
	if (ft_strcmp(tmp[1], use) == 0)
	{
		while (get_next_line(fd, &line))
		{
			if (line[0] == 'K' && line[1] == 'd' && line[2] == ' ')
			{
				each = ft_strsplit(line, ' ');
				obj->current_color.x = ft_atof(each[1]);
				obj->current_color.y = ft_atof(each[2]);
				obj->current_color.z = ft_atof(each[3]);
				while (each[iter])
					free(each[iter++]);
				free(each);
				iter = 0;
				break;
			}
			free(line);
		}
		free(line);
		while (tmp[iter])
			free(tmp[iter++]);
		free(tmp);
		return (1);
	}
	while (tmp[iter])
		free(tmp[iter++]);
	free(tmp);
	return (0);
}

void	load_material(char *str, t_obj *obj, char *path)
{
	char	*line;
	char	**tmp;
	int     iter;
	int     fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		throw_error(":PARSER: Incorrect material file name.");
	tmp = ft_strsplit(str, ' ');
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w' &&
		line[3] == 'm' && line[4] == 't' && line[5] == 'l' && line[6] == ' ')
			if (load_material_data(tmp[1], line, fd, obj))
				break;
		free(line);
	}
	free(line);
	iter = 0;
	while (tmp[iter])
		free(tmp[iter++]);
	free(tmp);
	close(fd);
}

char	*material_path(char *path)
{
	int	l;

	l = ft_strlen(path);
	path[l - 1] = 'l';
	path[l - 2] = 't';
	path[l - 3] = 'm';
	return (path);
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
	obj->data = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE * 4);
	obj->size_vertices = START_SIZE;
	obj->size_textures = START_SIZE;
	obj->size_normals = START_SIZE;
	obj->size_data = START_SIZE * 4;
	obj->nb_vertices = 0;
	obj->nb_textures = 0;
	obj->nb_normals = 0;
	obj->data_index = 0;
	obj->current_color = vec_new(0.64f, 0.64f, 0.64f);
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
		if (line[0] == 'u' && line[1] == 's' && line[2] == 'e' &&
		line[3] == 'm' && line[4] == 't' && line[5] == 'l' && line[6] == ' ')
			load_material(line, obj, material_path(path));
		if (line[0] == 'f' && line[1] == ' ')
			load_data(line, obj);
		free(line);
	}
	free(line);
	close(fd);
	if (obj->nb_normals == 0)
		init_normals(obj);
	ft_printf("This .obj has %d vertices.\n", obj->nb_vertices / 3);
	ft_printf("This .obj has %d textures coordinates.\n", obj->nb_textures / 2);
	if (obj->nb_normals)
		ft_printf("This .obj has %d normals.\n", obj->nb_normals / 3);
	else
		ft_printf("This .obj did not have normals. They are generated on program start.\n");
	ft_printf("This .obj has %d triangles.\n", obj->data_index / 3);
	return (obj);
}
