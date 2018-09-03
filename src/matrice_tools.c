/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:00:41 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/03 12:57:13 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLfloat	*translate4x4(float x, float y, float z)
{
	GLfloat	*u;

	u = matrice_4x4(NULL);
	u[12] = x;
	u[13] = y;
	u[14] = z;
	return (u);
}

void	rotate4x4_z(float theta, GLfloat *u)
{
	u[0] = cos(theta * M_PI / 180);
	u[4] = -sin(theta * M_PI / 180);
	u[1] = sin(theta * M_PI / 180);
	u[5] = cos(theta * M_PI / 180);
}

void	rotate4x4_y(float theta, GLfloat *u)
{
	u[0] = cos(theta * M_PI / 180);
	u[2] = -sin(theta * M_PI / 180);
	u[8] = sin(theta * M_PI / 180);
	u[10] = cos(theta * M_PI / 180);
}

void	rotate4x4_x(float theta, GLfloat *u)
{
	u[5] = cos(theta * M_PI / 180);
	u[9] = -sin(theta * M_PI / 180);
	u[6] = sin(theta * M_PI / 180);
	u[10] = cos(theta * M_PI / 180);
}

GLfloat	*scale_4x4(float scale)
{
	GLfloat	*u;

	u = matrice_4x4(NULL);
	u[0] = scale;
	u[5] = scale;
	u[10] = scale;
	return (u);
}
