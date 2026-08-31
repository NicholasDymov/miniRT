/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:58:02 by ndymov            #+#    #+#             */
/*   Updated: 2026/08/31 16:39:26 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <stdbool.h>

typedef struct s_vector3D
{
	float			x;
	float			y;
	float			z;
}					t_vector3D;

typedef t_vector3D	t_point3D;

typedef struct s_params
{
	float			d_n;
	float			co_n;
	float			r_2;
	float			a;
	float			b;
	float			c;
	t_vector3D		co;
}					t_params;

bool				v_equal(t_vector3D a, t_vector3D b);

t_vector3D			v_add(t_vector3D a, t_vector3D b);
t_vector3D			v_sub(t_vector3D a, t_vector3D b);
t_vector3D			v_scale(float s, t_vector3D a);
t_vector3D			v_normalize(t_vector3D a);
t_vector3D			v_cross(t_vector3D a, t_vector3D b);
t_vector3D			v_project(t_vector3D a, t_vector3D n);
t_vector3D			v_reflect(t_vector3D i, t_vector3D n);

float				v_dot(t_vector3D a, t_vector3D b);
float				v_square(t_vector3D a);
float				v_length(t_vector3D a);

bool				equal(float x, float y);
bool				range(float x, float start, float stop);
float				square(float x);

#endif
