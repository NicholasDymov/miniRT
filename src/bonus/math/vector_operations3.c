/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 07:37:24 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 08:20:37 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>
#include <stdbool.h>

t_vector3d	v_project(t_vector3d a, t_vector3d n)
{
	return (v_sub(a, v_scale(v_dot(a, n), n)));
}

t_vector3d	v_reflect(t_vector3d a, t_vector3d n)
{
	return (v_sub(v_scale(2.0f * v_dot(a, n), n), a));
}

t_vector3d	v_rotation(t_vector3d a, t_vector3d n, float angle)
{
	float		cosine;
	float		sine;
	t_vector3d	res;

	cosine = cosf(angle);
	sine = sinf(angle);
	res = v_scale(cosine, a);
	res = v_add(res, v_scale(sine, v_cross(n, a)));
	res = v_add(res, v_scale(v_dot(n, a) * (1.0f - cosine), n));
	return (v_normalize(res));
}

t_vector3d	v_orthonormal(t_vector3d a)
{
	if (fabsf(a.y) + RT_EPSILON > 1.0f)
		return (v_normalize(v_cross(a, (t_vector3d){1.0f, 0.0f, 0.0f})));
	else
		return (v_normalize(v_cross(a, (t_vector3d){0.0f, 1.0f, 0.0f})));
}
