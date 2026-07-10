/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 07:37:24 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/10 13:04:58 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>
#include <stdbool.h>

bool	v_equal(t_vector3D a, t_vector3D b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z));
}

t_vector3D	v_add(t_vector3D a, t_vector3D b)
{
	return ((t_vector3D){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3D	v_sub(t_vector3D a, t_vector3D b)
{
	return ((t_vector3D){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vector3D	v_scale(float s, t_vector3D a)
{
	return ((t_vector3D){s * a.x, s * a.y, s * a.z});
}

float	v_length_sq(t_vector3D a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

float	v_length(t_vector3D a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector3D	v_normalize(t_vector3D a)
{
	float	length;

	length = v_length(a);
	if (length == 0.0f)
		return ((t_vector3D){0.0f, 0.0f, 0.0f});
	return (v_scale(1.0f / length, a));
}

float	v_dot(t_vector3D a, t_vector3D b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector3D	v_cross(t_vector3D a, t_vector3D b)
{
	t_vector3D	p;

	p.x = a.y * b.z - a.z * b.y;
	p.y = a.z * b.x - a.x * b.z;
	p.z = a.x * b.y - a.y * b.x;
	return (p);
}

t_vector3D	v_reflect(t_vector3D i, t_vector3D n)
{
	return (v_sub(i, v_scale(2.0f * v_dot(i, n), n)));
}
