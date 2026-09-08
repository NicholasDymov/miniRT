/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_fast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 18:04:04 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

bool	intersect_sphere_fast(t_ray ray, const t_object *sphere, float max_dist)
{
	t_vector3d	co;
	float		b;
	float		d;
	float		d_sqrt;
	float		t;

	co = v_sub(ray.origin, sphere->center);
	b = v_dot(ray.dir, co);
	d = b * b - v_square(co) + sphere->radius * sphere->radius;
	if (d < 0.0f || -(b + sphere->radius) > max_dist)
		return (false);
	d_sqrt = sqrtf(d);
	t = -b - d_sqrt;
	if (t > RT_EPSILON && t <= max_dist)
		return (true);
	t = -b + d_sqrt;
	if (t > RT_EPSILON && t <= max_dist)
		return (true);
	return (false);
}
