/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:26:43 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/09 11:25:12 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3	vec_scalaire(t_vec3 u, float value)
{
	t_vec3 w;

	w.x = u.x * value;
	w.y = u.y * value;
	w.z = u.z * value;
	return (w);
}

t_vec3	vec_mult(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}

t_vec3	vec_sub(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

t_vec3	vec_add(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_vec3	vec_norm(t_vec3 u)
{
	t_vec3	w;
	float	length;

	if (vec_is_null(u))
		return (u);
	length = sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z));
	w.x = u.x / length;
	w.y = u.y / length;
	w.z = u.z / length;
	return (w);
}

GLfloat	*vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	GLfloat	*vec4;

	vec4 = (GLfloat *)malloc(sizeof(GLfloat) * 4);
	vec4[0] = x;
	vec4[1] = y;
	vec4[2] = z;
	vec4[3] = w;
	return (vec4);
}

float	vec_dotp(t_vec3 u, t_vec3 v)
{
	float ret;

	ret = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (ret);
}

t_vec3	vec_new(float x, float y, float z)
{
	t_vec3 vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}

float	dist_p(t_vec3 u, t_vec3 v)
{
	float dist;

	dist = sqrt(SQ(u.x - v.x) + SQ(u.y - v.y) + SQ(u.z - v.z));
	return (dist);
}

int		vec_is_null(t_vec3 u)
{
	if (u.x == 0 && u.y == 0 && u.z == 0)
		return (1);
	return (0);
}

t_vec3	cross_product(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = (u.y * v.z) - (u.z * v.y);
	w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
	return (w);
}
