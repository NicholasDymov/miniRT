/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 14:44:13 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

static inline t_hit	hit_build_surface(t_ray ray, float t, float direction,
		const t_object *cylinder)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	hit.normal = v_scale(direction / cylinder->radius,
			v_project(v_sub(hit.point, cylinder->center), cylinder->normal));
	hit.camera = v_scale(-1.0f, ray.direction);
	hit.color = cylinder->color;
	return (hit);
}

static inline t_hit	intersect_surface(t_ray ray, const t_object *cylinder,
		t_params *prms)
{
	float	d;
	float	d_sqrt;
	float	t;
	float	a_inv;

	prms->a = 1 - prms->d_n * prms->d_n;
	prms->b = v_dot(ray.direction, prms->co) - prms->d_n * prms->co_n;
	prms->c = v_square(prms->co) - prms->co_n * prms->co_n;
	if (prms->a < FT_EPSILON)
		return ((t_hit){.hit = false});
	d = prms->b * prms->b - prms->a * (prms->c - prms->r_2);
	if (d < 0.0f)
		return ((t_hit){.hit = false});
	d_sqrt = sqrtf(d);
	a_inv = 1.0f / prms->a;
	t = (-prms->b - d_sqrt) * a_inv;
	if (t > FT_EPSILON && fabsf(prms->co_n + t * prms->d_n) <= cylinder->height)
		return (hit_build_surface(ray, t, 1.0f, cylinder));
	t = (-prms->b + d_sqrt) * a_inv;
	if (t > FT_EPSILON && fabsf(prms->co_n + t * prms->d_n) <= cylinder->height)
		return (hit_build_surface(ray, t, -1.0f, cylinder));
	return ((t_hit){.hit = false});
}

static inline t_hit	hit_build_disk(t_ray ray, float t, t_vector3d normal,
		const t_object *object)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	hit.normal = normal;
	hit.camera = v_scale(-1.0f, ray.direction);
	hit.color = object->color;
	return (hit);
}

static inline t_hit	intersect_disk(t_ray ray, const t_object *cylinder,
		t_params *prms, float t_max)
{
	float		t1;
	float		t2;
	float		d_n_inv;
	t_vector3d	hit_normal;

	d_n_inv = 1.0f / prms->d_n;
	t1 = (-prms->co_n - cylinder->height) * d_n_inv;
	t2 = (-prms->co_n + cylinder->height) * d_n_inv;
	if (prms->d_n > 0.0f)
		hit_normal = v_scale(-1.0f, cylinder->normal);
	else
		hit_normal = cylinder->normal;
	if (t1 > FT_EPSILON && t1 < t_max && (t2 <= FT_EPSILON || t1 < t2)
		&& (prms->a * t1 + 2 * prms->b) * t1 + prms->c <= prms->r_2)
		return (hit_build_disk(ray, t1, hit_normal, cylinder));
	if (t2 > FT_EPSILON && t2 < t_max && (prms->a * t2 + 2 * prms->b) * t2
		+ prms->c <= prms->r_2)
		return (hit_build_disk(ray, t2, hit_normal, cylinder));
	else
		return ((t_hit){.hit = false});
}

t_hit	intersect_cylinder(t_ray ray, const t_object *cylinder)
{
	t_hit		hit_surface;
	t_hit		hit_disk;
	t_params	params;

	params.d_n = v_dot(ray.direction, cylinder->normal);
	params.co = v_sub(ray.origin, cylinder->center);
	params.co_n = v_dot(params.co, cylinder->normal);
	params.r_2 = cylinder->radius * cylinder->radius;
	hit_surface = intersect_surface(ray, cylinder, &params);
	if (equal(params.d_n, 0.0f))
		return (hit_surface);
	if (hit_surface.hit)
		hit_disk = intersect_disk(ray, cylinder, &params, hit_surface.distance);
	else
		hit_disk = intersect_disk(ray, cylinder, &params, INFINITY);
	if (hit_disk.hit && (!hit_surface.hit
			|| hit_disk.distance < hit_surface.distance))
		return (hit_disk);
	else
		return (hit_surface);
}
