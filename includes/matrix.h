/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 21:27:35 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/11/06 22:42:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct	s_matrix
{
	float		matrix[4][4];
}				t_matrix;

t_matrix		matrix_get_identity();
t_matrix		matrix_get_mult_matrix(const t_matrix *a, const t_matrix *b);
t_vector		matrix_get_mult_vector(const t_matrix *m, const t_vector *v);
t_vector		matrix_get_mult_dir_vector(const t_matrix *m, const t_vector *v);
t_matrix		matrix_get_rotation_x(const float a);
t_matrix		matrix_get_rotation_y(const float a);
t_matrix		matrix_get_rotation_z(const float a);
t_matrix		matrix_get_translation(const t_vector *trans);


#endif
