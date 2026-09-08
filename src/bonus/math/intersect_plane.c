/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 18:08:48 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>
#include <threads.h>

static inline t_hit	hit_build(t_ray ray, float t, t_vector3d normal,
		const t_object *object)
{
	t_hit		hit;
	t_vector3d	up;
	t_vector3d	cp;
	t_vector3d	e1;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.dir));
	hit.normal = normal;
	hit.camera = v_scale(-1.0f, ray.dir);
	if (object->surface == SURF_SOLID)
		return (hit.color = object->color, hit);
	if (fabsf(hit.normal.y) + RT_EPSILON > 1.0f)
		up = (t_vector3d){1.0f, 0.0f, 0.0f};
	else
		up = (t_vector3d){0.0f, 1.0f, 0.0f};
	cp = v_sub(hit.point, object->center);
	e1 = v_normalize(v_cross(hit.normal, up));
	hit.u = v_dot(cp, e1);
	hit.v = v_dot(cp, v_cross(hit.normal, e1));
	return (hit);
}

t_hit	intersect_plane(t_ray ray, const t_object *plane)
{
	float	t;
	float	numerator;
	float	denominator;

	denominator = v_dot(ray.dir, plane->normal);
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
