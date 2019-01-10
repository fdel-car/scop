/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:04:19 by fdel-car          #+#    #+#             */
/*   Updated: 2017/11/30 15:04:28 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
