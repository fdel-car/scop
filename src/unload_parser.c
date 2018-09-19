/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unload_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:40:15 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 14:57:25 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		throw_error(char *error)
{
	printf("ERROR:");
	printf("%s\n", error);
	exit(0);
}

void		load_vertices(char *line, t_obj *obj)
{
	char	**tab;
	int		iter;

	tab = ft_strsplit(line, ' ');
	iter = 0;
	while (tab[iter])
		iter++;
	if (iter > 4)
		throw_error(":PARSER: Wrong vertices line format in .obj");
	obj->nb_vertices += 3;
	while (obj->nb_vertices > obj->size_vertices)
	{
		printf("Not enough size in vertices, reallocating...\n");
		obj->size_vertices *= 2;
		obj->vertices = (GLfloat *)realloc(obj->vertices, sizeof(GLfloat) * obj->size_vertices);
		if (!obj->vertices)
			throw_error(":MEMORY: Malloc error, the vertices array is probably\
			getting too large.");
	}
	obj->vertices[obj->nb_vertices - 3] = atof(tab[1]) - obj->half_width;
	obj->vertices[obj->nb_vertices - 2] = atof(tab[2]) - obj->half_height;
	obj->vertices[obj->nb_vertices - 1] = atof(tab[3]) - obj->half_depth;
	free_tab(tab, 0);
}

void		load_textures(char *line, t_obj *obj)
{
	char	**tab;
	int		iter;

	tab = ft_strsplit(line, ' ');
	iter = 0;
	while (tab[iter])
		iter++;
	if (iter > 3)
		throw_error(":PARSER: Wrong texture coordinates line format in .obj");
	obj->nb_textures += 2;
	while (obj->nb_textures > obj->size_textures)
	{
		printf("Not enough size in textures, reallocating...\n");
		obj->size_textures *= 2;
		obj->textures = (GLfloat *)realloc(obj->textures, sizeof(GLfloat) *
															  obj->size_textures);
		if (!obj->textures)
			throw_error(":MEMORY: Malloc error, the texture coordinates array\
			is probably getting too large.");
	}
	obj->textures[obj->nb_textures - 2] = atof(tab[1]);
	obj->textures[obj->nb_textures - 1] = atof(tab[2]);
	free_tab(tab, 0);
}

void		load_normals(char *line, t_obj *obj)
{
	char	**tab;
	int		iter;

	tab = ft_strsplit(line, ' ');
	iter = 0;
	while (tab[iter])
		iter++;
	if (iter > 4)
		throw_error(":PARSER: Wrong normals line format in .obj");
	obj->nb_normals += 3;
	while (obj->nb_normals > obj->size_normals)
	{
		printf("Not enough size in normals, reallocating...\n");
		obj->size_normals *= 2;
		obj->normals = (GLfloat *)realloc(obj->normals, sizeof(GLfloat) *
															obj->size_normals);
		if (!obj->normals)
			throw_error(":MEMORY: Malloc error, the normals array is probably\
			getting too large.");
	}
	obj->normals[obj->nb_normals - 3] = atof(tab[1]);
	obj->normals[obj->nb_normals - 2] = atof(tab[2]);
	obj->normals[obj->nb_normals - 1] = atof(tab[3]);
	free_tab(tab, 0);
}

void		load_data_vertices(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * DATA_SIZE] = obj->vertices[index * 3];
	obj->data[obj->data_index * DATA_SIZE + 1] = obj->vertices[index * 3 + 1];
	obj->data[obj->data_index * DATA_SIZE + 2] = obj->vertices[index * 3 + 2];
}
