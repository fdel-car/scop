/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:46:32 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/29 14:51:10 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		generate_texture(char *path)
{
	GLuint texture;
	t_text *tex;

	tex = load_texture(path);
	if (!tex)
		return (-1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->tex_w, tex->tex_h, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, tex->img);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(tex->img);
	free(tex);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (texture);
}

int		fill_texture(t_text *tex, FILE *file)
{
	int		iter;
	int		tmp;
	int		tmp2;

	iter = 0;
	tmp = 0;
	while (iter++ < tex->tex_h)
	{
		tmp2 = 0;
		while (tmp2++ < tex->tex_w)
		{
			if (fread(tex->buff, 1, 4, file) <= 0)
				return (0);
			tex->img[tmp++] = tex->buff[3];
			tex->img[tmp++] = tex->buff[2];
			tex->img[tmp++] = tex->buff[1];
			tex->img[tmp++] = tex->buff[0];
		}
	}
	return (1);
}

t_text	*load_texture(char *path)
{
	FILE	*file;
	t_text	*tex;

	if ((file = fopen(path, "r")) <= 0)
		return (0);
	if (!(tex = malloc(sizeof(t_text))) && !fclose(file))
		return (0);
	if (fseek(file, 18, SEEK_SET) < 0 && !fclose(file))
		return (0);
	if (fread(tex->size, sizeof(int), 2, file) <= 0 && !fclose(file))
		return (0);
	tex->tex_w = tex->size[0];
	tex->tex_h = tex->size[1];
	if (fseek(file, 122, SEEK_SET) < 0 && !fclose(file))
		return (0);
	if (!(tex->img = (unsigned char *)malloc(sizeof(unsigned char) *
	(tex->tex_w * 4 * tex->tex_h))) && !fclose(file))
		return (0);
	if (!fill_texture(tex, file) && !fclose(file))
		return (0);
	fclose(file);
	return (tex);
}
