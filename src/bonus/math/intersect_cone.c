/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:11:34 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 18:02:20 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <float.h>
#include <math.h>

static inline t_hit	hit_build_surface(t_ray ray, float t, const t_object *cone)
{
	t_hit		hit;
	t_vector3d	cp;
	float		z;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.dir));
	cp = v_sub(hit.point, cone->center);
	z = v_dot(cp, cone->normal);
	hit.normal = v_normalize(v_sub(cp, v_scale(z * cone->r_2, cone->normal)));
	if (v_dot(hit.normal, ray.dir) > 0.0f)
		hit.normal = v_scale(-1.0f, hit.normal);
	hit.camera = v_scale(-1.0f, ray.dir);
	hit.color = cone->color;
	return (hit);
}

static inline float	intersect_surface(t_ray ray, const t_object *cone,
		t_params *prms)
{
	float	d;
	float	d_sqrt;
	float	t;
	float	a_inv;

	prms->a = 1 - cone->r_2 * prms->d_n * prms->d_n;
	prms->b = v_dot(ray.dir, prms->co) - cone->r_2 * prms->d_n * prms->co_n;
	prms->c = v_square(prms->co) - cone->r_2 * prms->co_n * prms->co_n;
	if (prms->a == 0.0f)
		return (FLT_MAX);
	d = prms->b * prms->b - prms->a * prms->c;
	if (d < 0.0f)
		return (FLT_MAX);
	d_sqrt = sqrtf(d);
	if (prms->a < 0.0f)
		d_sqrt = -d_sqrt;
	a_inv = 1.0f / prms->a;
	t = (-prms->b - d_sqrt) * a_inv;
	if (t > RT_EPSILON && range(prms->co_n + t * prms->d_n, 0.0f, cone->height))
		return (t);
	t = (-prms->b + d_sqrt) * a_inv;
	if (t > RT_EPSILON && range(prms->co_n + t * prms->d_n, 0.0f, cone->height))
		return (t);
	return (FLT_MAX);
}

static inline t_hit	hit_build_disk(t_ray ray, float t, const t_object *cone,
		float d_n)
{
	t_hit	hit;

	hit.hit = true;
	hit.point = v_add(ray.origin, v_scale(t, ray.dir));
	hit.distance = t;
	if (d_n > 0.0f)
		hit.normal = v_scale(-1.0f, cone->normal);
	else
		hit.normal = cone->normal;
	hit.color = cone->color;
	hit.camera = v_scale(-1.0f, ray.dir);
	return (hit);
}

static inline float	intersect_disk(const t_object *cone, t_params *prms)
{
	float	t;
	float	d_n_inv;

	d_n_inv = 1.0f / prms->d_n;
	t = (-prms->co_n + cone->height) * d_n_inv;
	if (t > RT_EPSILON && (prms->a * t + 2.0f * prms->b) * t + prms->c <= 0.0f)
		return (t);
	return (FLT_MAX);
}

t_hit	intersect_cone(t_ray ray, const t_object *cone)
{
	float		t_surface;
	float		t_disk;
	t_params	params;

	params.d_n = v_dot(ray.dir, cone->normal);
	params.co = v_sub(ray.origin, cone->center);
	params.co_n = v_dot(params.co, cone->normal);
	t_surface = intersect_surface(ray, cone, &params);
	if (equal(params.d_n, 0.0f))
		t_disk = FLT_MAX;
	else
		t_disk = intersect_disk(cone, &params);
	if (t_disk < t_surface)
		return (hit_build_disk(ray, t_disk, cone, params.d_n));
	else if (t_surface < FLT_MAX)
		return (hit_build_surface(ray, t_surface, cone));
	else
		return ((t_hit){.hit = false});
}
