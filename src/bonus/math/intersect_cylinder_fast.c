/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_fast.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 18:03:46 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <float.h>
#include <math.h>

static inline bool	intersect_surface(t_ray ray, const t_object *cylinder,
		t_params *prms, float max_dist)
{
	float	d;
	float	d_sqrt;
	float	t;
	float	a_inv;

	prms->a = 1 - prms->d_n * prms->d_n;
	prms->b = v_dot(ray.dir, prms->co) - prms->d_n * prms->co_n;
	prms->c = v_square(prms->co) - prms->co_n * prms->co_n;
	if (prms->a < RT_EPSILON)
		return (false);
	d = prms->b * prms->b - prms->a * (prms->c - cylinder->r_2);
	if (d < 0.0f)
		return (false);
	d_sqrt = sqrtf(d);
	a_inv = 1.0f / prms->a;
	t = (-prms->b - d_sqrt) * a_inv;
	if (t > RT_EPSILON && t < max_dist && fabsf(prms->co_n + t
			* prms->d_n) <= cylinder->height)
		return (true);
	t = (-prms->b + d_sqrt) * a_inv;
	if (t > RT_EPSILON && t < max_dist && fabsf(prms->co_n + t
			* prms->d_n) <= cylinder->height)
		return (true);
	return (false);
}

static inline bool	intersect_disk(const t_object *cylinder, t_params *prms,
		float max_dist)
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
	if (t1 > RT_EPSILON && t1 < max_dist && (prms->a * t1 + 2 * prms->b) * t1
		+ prms->c <= cylinder->r_2)
		return (true);
	if (t2 > RT_EPSILON && t2 < max_dist && (prms->a * t2 + 2 * prms->b) * t2
		+ prms->c <= cylinder->r_2)
		return (true);
	return (false);
}

bool	intersect_cylinder_fast(t_ray ray, const t_object *cylinder,
		float max_dist)
{
	t_params	params;

	params.d_n = v_dot(ray.dir, cylinder->normal);
	params.co = v_sub(ray.origin, cylinder->center);
	params.co_n = v_dot(params.co, cylinder->normal);
	if (intersect_surface(ray, cylinder, &params, max_dist))
		return (true);
	if (equal(params.d_n, 0.0f))
		return (false);
	return (intersect_disk(cylinder, &params, max_dist));
}
