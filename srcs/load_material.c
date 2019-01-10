/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:08:43 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 12:47:43 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		line_check(char *line, t_obj *obj)
{
	char	**each;

	if (line[0] == 'K' && line[1] == 'd' && line[2] == ' ')
	{
		each = ft_strsplit(line, ' ');
		obj->current_color.x = atof(each[1]);
		obj->current_color.y = atof(each[2]);
		obj->current_color.z = atof(each[3]);
		free_tab(each, 0);
	}
	else if (line[0] == 'm' && line[1] == 'a' && line[2] == 'p' && line[3]
	== '_' && line[4] == 'K' && line[5] == 'd' && line[6] == ' ')
	{
		obj->item_textured = 1;
		obj->tex_indice++;
		handle_texture(line, obj);
		return (-1);
	}
	else if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w' && line[3]
	== 'm' && line[4] == 't' && line[5] == 'l' && line[6] == ' ')
		return (-1);
	free(line);
	return (0);
}

int		load_material_data(char *use, char *new, int fd, t_obj *obj)
{
	char	**tmp;
	char	*line;

	tmp = ft_strsplit(new, ' ');
	if (strcmp(tmp[1], use) == 0)
	{
		while (get_next_line(fd, &line))
		{
			if (line_check(line, obj) < 0)
				break ;
		}
		free(line);
		free_tab(tmp, 0);
		return (1);
	}
	free_tab(tmp, 0);
	return (0);
}

void	load_material(char *str, t_obj *obj, char *path)
{
	char	*line;
	char	**tmp;
	int		fd;

	obj->item_textured = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		throw_error(":PARSER: Incorrect material file name.");
	tmp = ft_strsplit(str, ' ');
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'n' && line[1] == 'e' && line[2] == 'w' &&
		line[3] == 'm' && line[4] == 't' && line[5] == 'l' && line[6] == ' ')
			if (load_material_data(tmp[1], line, fd, obj))
				break ;
		free(line);
	}
	free(line);
	free_tab(tmp, 0);
	close(fd);
}

char	*material_path(char *path)
{
	int		l;

	l = strlen(path);
	path[l - 1] = 'l';
	path[l - 2] = 't';
	path[l - 3] = 'm';
	return (path);
}
