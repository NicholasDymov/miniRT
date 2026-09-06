/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:11:34 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/06 18:31:27 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

static inline t_hit	hit_build_surface(t_ray ray, float t, const t_object *cone)
{
	t_hit		hit;
	t_vector3d	cp;
	float		z;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	cp = v_sub(hit.point, cone->center);
	z = v_dot(cp, cone->normal);
	hit.normal = v_normalize(v_sub(v_project(cp, cone->normal), v_scale(z
					* cone->k_2, cone->normal)));
	if (v_dot(hit.normal, ray.direction) > 0.0f)
		hit.normal = v_scale(-1.0f, hit.normal);
	hit.camera = v_scale(-1.0f, ray.direction);
	hit.color = cone->color;
	return (hit);
}

static inline void	swap(float *t, float *s)
{
	float	tmp;

	if (*t <= *s)
		return ;
	tmp = *t;
	*t = *s;
	*s = tmp;
}

static inline t_hit	intersect_surface(t_ray ray, const t_object *cone,
		t_params *prms)
{
	float	d;
	float	d_sqrt;
	float	t;
	float	s;
	float	a_inv;

	prms->a = 1 - (1 + cone->k_2) * prms->d_n * prms->d_n;
	if (prms->a == 0.0f)
		return ((t_hit){.hit = false});
	prms->b = v_dot(ray.direction, prms->co) - (1 + cone->k_2) * prms->d_n
		* prms->co_n;
	prms->c = v_square(prms->co) - (1 + cone->k_2) * prms->co_n * prms->co_n;
	d = prms->b * prms->b - prms->a * prms->c;
	if (d < 0.0f)
		return ((t_hit){.hit = false});
	d_sqrt = sqrtf(d);
	a_inv = 1.0f / prms->a;
	t = (-prms->b - d_sqrt) * a_inv;
	s = (-prms->b + d_sqrt) * a_inv;
	swap(&t, &s);
	if (t > RT_EPSILON && range(prms->co_n + t * prms->d_n, 0.0f, cone->height))
		return (hit_build_surface(ray, t, cone));
	if (s > RT_EPSILON && range(prms->co_n + s * prms->d_n, 0.0f, cone->height))
		return (hit_build_surface(ray, s, cone));
	return ((t_hit){.hit = false});
}

static inline t_hit	intersect_disk(t_ray ray, const t_object *cone,
		t_params *prms, float t_max)
{
	float	t;
	float	d_n_inv;
	t_hit	hit;

	hit.hit = false;
	d_n_inv = 1.0f / prms->d_n;
	t = (-prms->co_n + cone->height) * d_n_inv;
	if (t <= RT_EPSILON || t >= t_max)
		return (hit);
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	if (v_square(v_project(v_sub(hit.point, cone->center),
				cone->normal)) > prms->r_2)
		return (hit);
	hit.hit = true;
	hit.distance = t;
	if (prms->d_n > 0.0f)
		hit.normal = v_scale(-1.0f, cone->normal);
	else
		hit.normal = cone->normal;
	hit.color = cone->color;
	hit.camera = v_scale(-1.0f, ray.direction);
	return (hit);
}

t_hit	intersect_cone(t_ray ray, const t_object *cone)
{
	t_hit		hit_surface;
	t_hit		hit_disk;
	t_params	params;

	params.d_n = v_dot(ray.direction, cone->normal);
	params.co = v_sub(ray.origin, cone->center);
	params.co_n = v_dot(params.co, cone->normal);
	params.r_2 = cone->radius * cone->radius;
	hit_surface = intersect_surface(ray, cone, &params);
	if (equal(params.d_n, 0.0f))
		return (hit_surface);
	if (hit_surface.hit)
		hit_disk = intersect_disk(ray, cone, &params, hit_surface.distance);
	else
		hit_disk = intersect_disk(ray, cone, &params, INFINITY);
	if (hit_disk.hit && (!hit_surface.hit
			|| hit_disk.distance < hit_surface.distance))
		return (hit_disk);
	else
		return (hit_surface);
}
