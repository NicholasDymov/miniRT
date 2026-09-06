/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/06 09:24:31 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"

static inline t_hit	hit_build(t_ray ray, float t, t_vector3d normal,
		const t_object *object)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	hit.normal = normal;
	hit.color = object->color;
	return (hit);
}

t_hit	intersect_plane(t_ray ray, const t_object *plane)
{
	float	t;
	float	numerator;
	float	denominator;

	denominator = v_dot(ray.direction, plane->normal);
	if (equal(denominator, 0.0f))
		return ((t_hit){.hit = false});
	numerator = v_dot(v_sub(plane->center, ray.origin), plane->normal);
	t = numerator / denominator;
	if (t <= RT_EPSILON)
		return ((t_hit){.hit = false});
	if (denominator > 0.0f)
		return (hit_build(ray, t, v_scale(-1.0f, plane->normal), plane));
	else
		return (hit_build(ray, t, plane->normal, plane));
}
