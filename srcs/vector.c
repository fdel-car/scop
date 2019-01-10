/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:26:43 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/30 15:03:24 by fdel-car         ###   ########.fr       */
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
