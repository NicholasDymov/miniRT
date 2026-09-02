/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 07:37:24 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/02 16:43:09 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>
#include <stdbool.h>

float	v_square(t_vector3D a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

float	v_length(t_vector3D a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
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
