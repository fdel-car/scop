/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 17:58:38 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/30 15:00:37 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat	*identity_4x4(GLfloat *matrice)
{
	int		iter;

	iter = 0;
	while (iter < 16)
	{
		matrice[iter] = 0.0f;
		if (iter % 5 == 0)
			matrice[iter] = 1.0f;
		iter++;
	}
	return (matrice);
}

GLfloat	*matrice_4x4(GLfloat *u, ...)
{
	GLfloat	*matrice;
	int		iter;
	int		tmp;
	GLfloat	*vect;
	va_list ap;

	iter = 0;
	matrice = (GLfloat *)malloc(sizeof(GLfloat) * 16);
	if (u == NULL)
		return (identity_4x4(matrice));
	va_start(ap, u);
	vect = u;
	while (vect)
	{
		tmp = 0;
		while (iter < 16 && tmp < 4)
			matrice[iter++] = vect[tmp++];
		free(vect);
		vect = va_arg(ap, GLfloat *);
	}
	va_end(ap);
	if (iter < 16)
		return (identity_4x4(matrice));
	return (matrice);
}

GLfloat	*perspective_projection(float fov, float aspect, float near, float far)
{
	GLfloat	*u;
	float	tan_fov;

	u = matrice_4x4(NULL);
	tan_fov = 1 / tan((fov * M_PI / 180.0f) / 2);
	u[0] = tan_fov / aspect;
	u[5] = tan_fov;
	u[10] = -(far + near) / (far - near);
	u[14] = (-2.0f * far * near) / (far - near);
	u[11] = -1;
	u[15] = 0;
	return (u);
}

GLfloat	*look_at4x4(t_vec3 cam, t_vec3 target, t_vec3 up)
{
	GLfloat	*u;
	t_vec3	right;
	t_vec3	up_final;
	t_vec3	dir;

	u = matrice_4x4(NULL);
	dir = vec_norm(vec_sub(target, cam));
	right = vec_norm(cross_product(dir, up));
	up_final = cross_product(right, dir);
	u[0] = right.x;
	u[4] = right.y;
	u[8] = right.z;
	u[1] = up_final.x;
	u[5] = up_final.y;
	u[9] = up_final.z;
	u[2] = -dir.x;
	u[6] = -dir.y;
	u[10] = -dir.z;
	u[12] = -vec_dotp(right, cam);
	u[13] = -vec_dotp(up_final, cam);
	u[14] = vec_dotp(dir, cam);
	return (u);
}

GLfloat	*mult_matrice4x4(GLfloat *u, GLfloat *v)
{
	GLfloat *w;
	int		iter;
	int		tmp;

	w = matrice_4x4(NULL);
	iter = 0;
	while (iter < 4)
	{
		tmp = 0;
		while (tmp < 4)
		{
			w[iter * 4 + tmp] = u[tmp] * v[iter * 4] + u[4 + tmp] *
			v[iter * 4 + 1] + u[8 + tmp] * v[iter * 4 + 2] +
			u[12 + tmp] * v[iter * 4 + 3];
			tmp++;
		}
		iter++;
	}
	return (w);
}
