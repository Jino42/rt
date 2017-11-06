/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 21:34:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/06 22:47:14 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix		matrix_get_identity()
{
	t_matrix m;

	m.matrix[0][0] = 1;
	m.matrix[0][1] = 0;
	m.matrix[0][2] = 0;
	m.matrix[0][3] = 0;
	m.matrix[1][0] = 0;
	m.matrix[1][1] = 1;
	m.matrix[1][2] = 0;
	m.matrix[1][3] = 0;
	m.matrix[2][0] = 0;
	m.matrix[2][1] = 0;
	m.matrix[2][2] = 1;
	m.matrix[2][3] = 0;
	m.matrix[3][0] = 0;
	m.matrix[3][1] = 0;
	m.matrix[3][2] = 0;
	m.matrix[3][3] = 1;
	return (m);
}

t_matrix		matrix_get_mult_matrix(const t_matrix *a, const t_matrix *b)
{
	int			x;
	int			y;
	float		temp;
	t_matrix	new;

	new = matrix_get_identity();
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{///////////////////////////////////////////////////PAS BON !!!! RAPPEL TOA
			temp = a->matrix[y][0] * b->matrix[0][x];
			temp = temp + a->matrix[y][1] * b->matrix[1][x];
			temp = temp + a->matrix[y][2] * b->matrix[2][x];
			temp = temp + a->matrix[y][3] * b->matrix[3][x];
			new.matrix[y][x] = temp;
			x++;
		}
		y++;
	}
	return (new);
}

t_vector		matrix_get_mult_vector(const t_matrix *m, const t_vector *v)
{
	t_vector	new;
	float		len;

	new.x = (m->matrix[0][0] * v->x) + (m->matrix[0][1] * v->y) + (m->matrix[0][2] * v->z) + (m->matrix[0][3]);
	new.y = (m->matrix[1][0] * v->x) + (m->matrix[1][1] * v->y) + (m->matrix[1][2] * v->z) + (m->matrix[1][3]);
	new.z = (m->matrix[2][0] * v->x) + (m->matrix[2][1] * v->y) + (m->matrix[2][2] * v->z) + (m->matrix[2][3]);
	len =   (m->matrix[3][0] * v->x) + (m->matrix[3][1] * v->y) + (m->matrix[3][2] * v->z) + (m->matrix[3][3]);

/*
new.x = (m->matrix[0][0] * v->x) + (m->matrix[1][0] * v->y) + (m->matrix[2][0] * v->z) + (m->matrix[3][0]);
new.y = (m->matrix[0][1] * v->x) + (m->matrix[1][1] * v->y) + (m->matrix[2][1] * v->z) + (m->matrix[3][1]);
new.z = (m->matrix[0][2] * v->x) + (m->matrix[1][2] * v->y) + (m->matrix[2][2] * v->z) + (m->matrix[3][2]);
len =   (m->matrix[0][3] * v->x) + (m->matrix[1][3] * v->y) + (m->matrix[2][3] * v->z) + (m->matrix[3][3]);
*/
	new.x /= len;
	new.y /= len;
	new.z /= len;

	return (new);
}

t_vector		matrix_get_mult_dir_vector(const t_matrix *m, const t_vector *v)
{
	t_vector n;

	n.x = (v->x * m->matrix[0][0]) + (v->y * m->matrix[0][1]) + (v->z * m->matrix[0][2]);
	n.y = (v->x * m->matrix[1][0]) + (v->y * m->matrix[1][1]) + (v->z * m->matrix[1][2]);
	n.z = (v->x * m->matrix[2][0]) + (v->y * m->matrix[2][1]) + (v->z * m->matrix[2][2]);
	return (n);
}

t_matrix	matrix_get_rotation_x(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[1][1] = cos(a);
	new.matrix[2][2] = cos(a);
	new.matrix[1][2] = -sin(a);
	new.matrix[2][1] = sin(a);

	return (new);
}

t_matrix	matrix_get_rotation_y(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[2][0] = -sin(a);
	new.matrix[2][2] = cos(a);
	new.matrix[0][2] = sin(a);

	return (new);
}

t_matrix	matrix_get_rotation_z(const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[0][1] = -sin(a);
	new.matrix[1][0] = sin(a);
	new.matrix[1][1] = cos(a);

	return (new);
}

t_matrix	matrix_get_translation(const t_vector *trans)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][3] = trans->x;
	new.matrix[1][3] = trans->y;
	new.matrix[2][3] = trans->z;
	return (new);
}
