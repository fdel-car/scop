/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:16:01 by fdel-car          #+#    #+#             */
/*   Updated: 2017/12/06 16:00:33 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_normals(t_obj *obj, int iter)
{
	int		tmp;
	t_vec3	u[4];

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

void	set_texture(t_obj *obj)
{
	int		iter;
	char	*tmp;
	char	*nbr;

	iter = 0;
	while (iter <= obj->tex_indice)
	{
		nbr = ft_itoa(iter);
		glActiveTexture(GL_TEXTURE0 + iter);
		glBindTexture(GL_TEXTURE_2D, obj->sampler2d[iter]);
		tmp = ft_strjoin("obj_texture[", nbr);
		free(nbr);
		nbr = ft_strjoin(tmp, "]");
		free(tmp);
		glUniform1i(glGetUniformLocation(g_env.shader_program, nbr), iter);
		free(nbr);
		iter++;
	}
}

int		end_by(char *s, char *end)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (s[++i])
		;
	while (end[++j])
		;
	i--;
	j--;
	while (j >= 0 && end[j] && s[i])
	{
		if (s[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}

void	handle_texture(char *line, t_obj *obj)
{
	char	**tab;
	char	*path;

	tab = ft_strsplit(line, ' ');
	path = ft_strjoin(obj->path, tab[1]);
	if (end_by(path, ".bmp"))
		obj->sampler2d[obj->tex_indice] = generate_texture(path);
	if (obj->sampler2d[obj->tex_indice] != -1)
	{
		g_env.textured = 1;
		g_env.coeff_texture = 1.0f;
	}
	glActiveTexture(GL_TEXTURE0 + obj->tex_indice);
	free_tab(tab, 0);
	free(path);
}
