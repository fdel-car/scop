/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:49:57 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 14:55:49 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		load_data_textures(t_obj *obj, int index)
{
	if (index < 0)
		throw_error(":PARSER: Negative indexes on faces.");
	obj->data[obj->data_index * DATA_SIZE + 3] = obj->textures[index * 2];
	obj->data[obj->data_index * DATA_SIZE + 4] = obj->textures[index * 2 + 1];
}

void		obj_init_data(t_obj *obj)
{
	obj->min_x = INT_MAX;
	obj->min_y = INT_MAX;
	obj->min_z = INT_MAX;
	obj->max_x = INT_MIN;
	obj->max_y = INT_MIN;
	obj->max_z = INT_MIN;
	obj->range = 0;
	obj->use_mtl = 0;
}

void		loop_pre_compute(char *line, t_obj *obj)
{
	char	**tab;
	float	tmp;

	if (line[0] == 'v' & line[1] == ' ')
	{
		tab = ft_strsplit(line, ' ');
		tmp = atof(tab[1]);
		if (tmp < obj->min_x)
			obj->min_x = tmp;
		if (tmp > obj->max_x)
			obj->max_x = tmp;
		tmp = atof(tab[2]);
		if (tmp < obj->min_y)
			obj->min_y = tmp;
		if (tmp > obj->max_y)
			obj->max_y = tmp;
		tmp = atof(tab[3]);
		if (tmp < obj->min_z)
			obj->min_z = tmp;
		if (tmp > obj->max_z)
			obj->max_z = tmp;
		free_tab(tab, 0);
		obj->nb_vertices++;
	}
	free(line);
}

void		check_validity(char *line, t_obj *obj)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!isascii(line[i]))
		{
			free(line);
			throw_error(":PARSER: Invalid characters found, \
most likely not an obj file.");
		}
		i++;
	}
	if (line[0] == 'm' && line[1] == 't' && line[2] == 'l' &&
		line[3] == 'l' && line[4] == 'i' && line[5] == 'b' && line[6] == ' ')
		obj->use_mtl = 1;
}

void		pre_compute_data(char *path, t_obj *obj)
{
	int		fd;
	char	*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return ;
	obj_init_data(obj);
	while (get_next_line(fd, &line))
	{
		check_validity(line, obj);
		loop_pre_compute(line, obj);
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
