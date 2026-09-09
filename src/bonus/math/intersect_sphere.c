/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 09:18:52 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

static inline t_hit	hit_build(t_ray ray, float t, float direction,
		const t_object *sphere)
{
	t_hit	hit;
	float	u;
	float	v;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.dir));
	hit.normal = v_scale(direction * sphere->radius_inv, v_sub(hit.point,
				sphere->center));
	hit.camera = v_scale(-1.0f, ray.dir);
	hit.color = sphere->color;
	if (sphere->surface == SURF_SOLID)
		return (hit);
	u = 0.5f + atan2f(hit.normal.z, hit.normal.x) * (0.5f / M_PI);
	v = fminf(1.0f - RT_EPSILON, acosf(fmaxf(-1.0f, fminf(1.0f, hit.normal.y)))
			* (1.0f / M_PI));
	if (sphere->surface == SURF_CHECK)
		hit.color = color_checker(u * 20, v * 10, sphere->color,
				sphere->color_alt);
	else
		hit.normal = color_bump(u, v, hit.normal, sphere->bump_map);
	return (hit);
}

t_hit	intersect_sphere(t_ray ray, const t_object *sphere)
{
	t_vector3d	co;
	float		b;
	float		d;
	float		d_sqrt;
	float		t;

	co = v_sub(ray.origin, sphere->center);
	b = v_dot(ray.dir, co);
	d = b * b - v_square(co) + sphere->radius * sphere->radius;
	if (d < 0.0f)
		return ((t_hit){.hit = false});
	d_sqrt = sqrtf(d);
	t = -b - d_sqrt;
	if (t > RT_EPSILON)
		return (hit_build(ray, t, 1.0f, sphere));
	t = -b + d_sqrt;
	if (t > RT_EPSILON)
		return (hit_build(ray, t, -1.0f, sphere));
	return ((t_hit){.hit = false});
}
