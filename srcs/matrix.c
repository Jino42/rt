/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 21:34:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/07 22:49:16 by ntoniolo         ###   ########.fr       */
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
		{
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

void	matrix_rotation_x(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[1][1] = cos(a);
	new.matrix[2][2] = cos(a);
	new.matrix[1][2] = -sin(a);
	new.matrix[2][1] = sin(a);
	*m = matrix_get_mult_matrix(m, &new);

	return ;
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

void		matrix_rotation_y(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[2][0] = -sin(a);
	new.matrix[2][2] = cos(a);
	new.matrix[0][2] = sin(a);
	*m = matrix_get_mult_matrix(m, &new);

	return ;
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

void		matrix_rotation_z(t_matrix *m, const float a)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][0] = cos(a);
	new.matrix[0][1] = -sin(a);
	new.matrix[1][0] = sin(a);
	new.matrix[1][1] = cos(a);
	*m = matrix_get_mult_matrix(m, &new);

	return ;
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

void		matrix_translation(t_matrix *m, const t_vector *trans)
{
	t_matrix new;

	new = matrix_get_identity();
	new.matrix[0][3] = trans->x;
	new.matrix[1][3] = trans->y;
	new.matrix[2][3] = trans->z;
	*m = matrix_get_mult_matrix(m, &new);
	return ;
}

void 		matrix_string(const t_matrix *m)
{
	int x;
	int y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			printf("%.2f", m->matrix[y][x]);
			if (x < 3)
				printf(" | ");
			x++;
		}
		printf("\n");
		y++;
	}
}

t_matrix inverse(t_matrix *t)
{
	int i, j, k;
	t_matrix aa;
	t_matrix *s = &aa;

	// Forward elimination
	for (i = 0; i < 3 ; i++)
	{
		int pivot = i;

		float pivotsize = t->matrix[i][i];

		if (pivotsize < 0)
			pivotsize = -pivotsize;
		for (j = i + 1; j < 4; j++)
		{
			float tmp = t->matrix[j][i];
			if (tmp < 0)
				tmp = -tmp;
			if (tmp > pivotsize)
			{
				pivot = j;
				pivotsize = tmp;
			}
		}
		if (pivotsize == 0)
		{
			return matrix_get_identity();
		}

		if (pivot != i)
		{
			for (j = 0; j < 4; j++)
			{
				float tmp;

				tmp = t->matrix[i][j];
				t->matrix[i][j] = t->matrix[pivot][j];
				t->matrix[pivot][j] = tmp;

				tmp = s->matrix[i][j];
				s->matrix[i][j] = s->matrix[pivot][j];
				s->matrix[pivot][j] = tmp;
			}
		}

		for (j = i + 1; j < 4; j++)
		{
			float f = t->matrix[j][i] / t->matrix[i][i];

			for (k = 0; k < 4; k++)
			{
				t->matrix[j][k] -= f * t->matrix[i][k];
				s->matrix[j][k] -= f * s->matrix[i][k];
			}
		}
	}

	// Backward substitution
	for (i = 3; i >= 0; --i)
	{
		float f;

		if ((f = t->matrix[i][i]) == 0)
		{
			// Cannot invert singular matrix
			return matrix_get_identity();
		}

		for (j = 0; j < 4; j++)
		{
			t->matrix[i][j] /= f;
			s->matrix[i][j] /= f;
		}

		for (j = 0; j < i; j++)
		{
			f = t->matrix[j][i];

			for (k = 0; k < 4; k++)
			{
				t->matrix[j][k] -= f * t->matrix[i][k];
				s->matrix[j][k] -= f * s->matrix[i][k];
			}
		}
	}
	return *s;
}
