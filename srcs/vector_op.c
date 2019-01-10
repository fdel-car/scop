/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:03:04 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/30 15:04:00 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

float	vec_dotp(t_vec3 u, t_vec3 v)
{
	float ret;

	ret = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (ret);
}

t_vec3	cross_product(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = (u.y * v.z) - (u.z * v.y);
	w.y = (u.z * v.x) - (u.x * v.z);
	w.z = (u.x * v.y) - (u.y * v.x);
	return (w);
}
