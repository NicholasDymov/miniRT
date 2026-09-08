/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 11:22:26 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <float.h>
#include <math.h>

static inline t_hit	hit_build_surface(t_ray ray, float t,
		const t_object *cylinder)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	hit.normal = v_scale(1.0f / cylinder->radius, v_project(v_sub(hit.point,
					cylinder->center), cylinder->normal));
	if (v_dot(hit.normal, ray.direction) > 0.0f)
		hit.normal = v_scale(-1.0f, hit.normal);
	hit.color = cylinder->color;
	return (hit);
}

static inline float	intersect_surface(t_ray ray, const t_object *cylinder,
		t_params *prms)
{
	float	d;
	float	d_sqrt;
	float	t;
	float	a_inv;

	prms->a = 1 - prms->d_n * prms->d_n;
	prms->b = v_dot(ray.direction, prms->co) - prms->d_n * prms->co_n;
	prms->c = v_square(prms->co) - prms->co_n * prms->co_n;
	if (prms->a < RT_EPSILON)
		return (FLT_MAX);
	d = prms->b * prms->b - prms->a * (prms->c - prms->r_2);
	if (d < 0.0f)
		return (FLT_MAX);
	d_sqrt = sqrtf(d);
	a_inv = 1.0f / prms->a;
	t = (-prms->b - d_sqrt) * a_inv;
	if (t > RT_EPSILON && fabsf(prms->co_n + t * prms->d_n) <= cylinder->height)
		return (t);
	t = (-prms->b + d_sqrt) * a_inv;
	if (t > RT_EPSILON && fabsf(prms->co_n + t * prms->d_n) <= cylinder->height)
		return (t);
	return (FLT_MAX);
}

static inline t_hit	hit_build_disk(t_ray ray, float t, const t_object *cylinder,
		float d_n)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	if (d_n > 0.0f)
		hit.normal = v_scale(-1.0f, cylinder->normal);
	else
		hit.normal = cylinder->normal;
	hit.color = cylinder->color;
	return (hit);
}

static inline float	intersect_disk(const t_object *cylinder, t_params *prms)
{
	float	t1;
	float	t2;
	float	d_n_inv;

	d_n_inv = 1.0f / prms->d_n;
	if (d_n_inv > 0.0f)
	{
		t1 = (-prms->co_n - cylinder->height) * d_n_inv;
		t2 = (-prms->co_n + cylinder->height) * d_n_inv;
	}
	else
	{
		t1 = (-prms->co_n + cylinder->height) * d_n_inv;
		t2 = (-prms->co_n - cylinder->height) * d_n_inv;
	}
	if (t1 > RT_EPSILON && (prms->a * t1 + 2 * prms->b) * t1
		+ prms->c <= prms->r_2)
		return (t1);
	if (t2 > RT_EPSILON && (prms->a * t2 + 2 * prms->b) * t2
		+ prms->c <= prms->r_2)
		return (t2);
	return (FLT_MAX);
}

t_hit	intersect_cylinder(t_ray ray, const t_object *cylinder)
{
	float		t_surface;
	float		t_disk;
	t_params	params;

	params.d_n = v_dot(ray.direction, cylinder->normal);
	params.co = v_sub(ray.origin, cylinder->center);
	params.co_n = v_dot(params.co, cylinder->normal);
	params.r_2 = cylinder->radius * cylinder->radius;
	t_surface = intersect_surface(ray, cylinder, &params);
	if (equal(params.d_n, 0.0f))
		t_disk = FLT_MAX;
	else
		t_disk = intersect_disk(cylinder, &params);
	if (t_disk < t_surface)
		return (hit_build_disk(ray, t_disk, cylinder, params.d_n));
	else if (t_surface < FLT_MAX)
		return (hit_build_surface(ray, t_surface, cylinder));
	else
		return ((t_hit){.hit = false});
}
