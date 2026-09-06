/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 07:37:24 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 09:30:46 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdbool.h>

bool	v_equal(t_vector3d a, t_vector3d b)
{
	return (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z));
}

t_vector3d	v_add(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector3d	v_sub(t_vector3d a, t_vector3d b)
{
	return ((t_vector3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vector3d	v_scale(float s, t_vector3d a)
{
	return ((t_vector3d){s * a.x, s * a.y, s * a.z});
}

t_vector3d	v_normalize(t_vector3d a)
{
	float	length;

	length = v_length(a);
	if (length == 0.0f)
		return ((t_vector3d){0.0f, 0.0f, 0.0f});
	return (v_scale(1.0f / length, a));
}
