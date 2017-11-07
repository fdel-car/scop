/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:59:30 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/07 20:26:07 by fdel-car         ###   ########.fr       */
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
	}
	obj->vertices[obj->nb_vertices - 3] = ft_atof(tab[1]);
	obj->vertices[obj->nb_vertices - 2] = ft_atof(tab[2]);
	obj->vertices[obj->nb_vertices - 1] = ft_atof(tab[3]);
	iter = 0;
	while (tab[iter])
		free(tab[iter++]);
	free(tab);
}

void	load_data_vertices(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * 3] = obj->vertices[index * 3];
	obj->data[obj->data_index * 3 + 1] = obj->vertices[index * 3 + 1];
	obj->data[obj->data_index * 3 + 2] = obj->vertices[index * 3 + 2];
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
			while ((obj->data_index + 1) * 3 > obj->size_data)
			{
				ft_putendl("Not enough size in data array, reallocing...");
				obj->size_data *= 2;
				obj->data = (GLfloat *)realloc(obj->data, sizeof(GLfloat) * obj->size_data);
			}
			tmp = 0;
			each = ft_strsplit(tab[iter], '/');
			if (each[tmp])
				load_data_vertices(obj, ft_atoi(each[tmp]) - 1);
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

t_obj	*load_obj(char *path)
{
	char	*line;
	int     fd;
	t_obj   *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->vertices = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->data = (GLfloat *)malloc(sizeof(GLfloat) * START_SIZE);
	obj->size_vertices = START_SIZE;
	obj->size_data = START_SIZE;
	obj->nb_vertices = 0;
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
		if (line[0] == 'f' && line[1] == ' ')
			load_data(line, obj);
		free(line);
	}
	free(line);
	printf("This .obj has %d vertices.\n", obj->nb_vertices / 3);
	printf("This .obj has %d triangles.\n", obj->data_index / 3);
	return (obj);
}
