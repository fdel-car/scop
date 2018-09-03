/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:23:49 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/03 16:44:54 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		fill_data(char *str, t_obj *obj)
{
	char	**each;
	int		tmp;

	tmp = 0;
	each = ft_strsplit(str, '/');
	if (each[tmp] && obj->nb_vertices)
		load_data_vertices(obj, ft_atoi(each[tmp++]) - 1);
	if (each[tmp] && obj->nb_textures)
		load_data_textures(obj, ft_atoi(each[tmp++]) - 1);
	if (each[tmp] && obj->nb_normals)
		load_data_normals(obj, ft_atoi(each[tmp++]) - 1);
	obj->data[obj->data_index * DATA_SIZE + 8] = obj->current_color.x;
	obj->data[obj->data_index * DATA_SIZE + 9] = obj->current_color.y;
	obj->data[obj->data_index * DATA_SIZE + 10] = obj->current_color.z;
	if (obj->item_textured == 1)
		obj->data[obj->data_index * DATA_SIZE + 11] =\
		(float)obj->tex_indice + EPSILON;
	else
		obj->data[obj->data_index * DATA_SIZE + 11] = -1.0f - EPSILON;
	free_tab(each, 0);
	obj->data_index++;
}

void		upgrade_array(t_obj *obj)
{
	while ((obj->data_index + 1) * DATA_SIZE > obj->size_data)
	{
		ft_putendl("Not enough size in data array, reallocating...");
		obj->size_data *= 2;
		obj->data = (GLfloat *)realloc(obj->data, sizeof(GLfloat) *\
		obj->size_data);
		if (!obj->data)
			throw_error(":MEMORY: Malloc error, the data array is\
			probably getting too large.");
	}
}

void		unload_load_data(int iter, char **tab, t_obj *obj)
{
	iter = 1;
	while (iter < 4)
	{
		upgrade_array(obj);
		fill_data(tab[iter], obj);
		iter++;
	}
	iter = 3;
	while (iter != 2)
	{
		upgrade_array(obj);
		fill_data(tab[iter], obj);
		iter++;
		if (iter == 5)
			iter = 1;
	}
}

void		load_data(char *line, t_obj *obj)
{
	char	**tab;
	int		iter;

	tab = ft_strsplit(line, ' ');
	iter = 0;
	while (tab[iter])
		iter++;
	if (iter == 4)
	{
		iter = 1;
		while (iter < 4)
		{
			upgrade_array(obj);
			fill_data(tab[iter], obj);
			iter++;
		}
	}
	else if (iter == 5)
		unload_load_data(iter, tab, obj);
	else if (iter > 5)
		throw_error(":PARSER: The .obj has complex polygon with more than\
		4 sides.");
	free_tab(tab, 0);
}
