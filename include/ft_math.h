/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:58:02 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/10 13:17:32 by ndymov           ###   ########.fr       */
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

bool				v_equal(t_vector3D a, t_vector3D b);

t_vector3D			v_add(t_vector3D a, t_vector3D b);
t_vector3D			v_sub(t_vector3D a, t_vector3D b);
t_vector3D			v_scale(float s, t_vector3D a);
t_vector3D			v_normalize(t_vector3D a);
t_vector3D			v_cross(t_vector3D a, t_vector3D b);
t_vector3D			v_reflect(t_vector3D i, t_vector3D n);

float				v_dot(t_vector3D a, t_vector3D b);
float				v_length_sq(t_vector3D a);
float				v_length(t_vector3D a);

bool				equal(float x, float y);
bool				range(float x, float start, float stop);

#endif
