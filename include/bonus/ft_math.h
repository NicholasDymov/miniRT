/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:58:02 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 08:20:59 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <stdbool.h>

typedef struct s_vector3d
{
	float			x;
	float			y;
	float			z;
}					t_vector3d;

typedef t_vector3d	t_point3d;

typedef struct s_params
{
	float			d_n;
	float			co_n;
	float			a;
	float			b;
	float			c;
	t_vector3d		co;
}					t_params;

bool				v_equal(t_vector3d a, t_vector3d b);

t_vector3d			v_add(t_vector3d a, t_vector3d b);
t_vector3d			v_sub(t_vector3d a, t_vector3d b);
t_vector3d			v_scale(float s, t_vector3d a);
t_vector3d			v_normalize(t_vector3d a);
t_vector3d			v_cross(t_vector3d a, t_vector3d b);
t_vector3d			v_project(t_vector3d a, t_vector3d n);
t_vector3d			v_reflect(t_vector3d i, t_vector3d n);
t_vector3d			v_orthonormal(t_vector3d a);

t_vector3d			v_rotation(t_vector3d a, t_vector3d n, float angle);

float				v_dot(t_vector3d a, t_vector3d b);
float				v_square(t_vector3d a);
float				v_length(t_vector3d a);

bool				equal(float x, float y);
bool				range(float x, float start, float stop);
float				square(float x);
float				pow32(float x);

#endif
