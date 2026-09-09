/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 09:55:39 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"

static inline t_hit	hit_build(t_ray ray, float t, t_vector3d normal,
		const t_object *object)
{
	t_hit		hit;
	t_vector3d	cp;
	t_vector3d	e1;
	float		u;
	float		v;

	hit = (t_hit){.hit = true, .distance = t, .normal = normal};
	hit.point = v_add(ray.origin, v_scale(t, ray.dir));
	hit.camera = v_scale(-1.0f, ray.dir);
	hit.color = object->color;
	if (object->surface == SURF_SOLID)
		return (hit);
	e1 = v_orthonormal(hit.normal);
	cp = v_sub(hit.point, object->center);
	u = v_dot(cp, e1) * 0.1f;
	v = v_dot(cp, v_cross(hit.normal, e1)) * 0.1f;
	if (object->surface == SURF_CHECK)
		hit.color = color_checker(u, v, object->color, object->color_alt);
	else
		hit.normal = color_bump(u, v, hit.normal, object->bump_map);
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
