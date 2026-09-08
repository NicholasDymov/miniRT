/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_fast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 13:11:34 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 18:17:27 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <float.h>
#include <math.h>

static inline bool	intersect_surface(t_ray ray, const t_object *cone,
		t_params *prms, float max_dist)
{
	float	d;
	float	d_sqrt;
	float	t;
	float	a_inv;

	prms->a = 1 - cone->r_2 * prms->d_n * prms->d_n;
	prms->b = v_dot(ray.dir, prms->co) - cone->r_2 * prms->d_n * prms->co_n;
	prms->c = v_square(prms->co) - cone->r_2 * prms->co_n * prms->co_n;
	d = prms->b * prms->b - prms->a * prms->c;
	if (d < 0.0f || prms->a == 0.0f)
		return (false);
	d_sqrt = sqrtf(d);
	if (prms->a < 0.0f)
		d_sqrt = -d_sqrt;
	a_inv = 1.0f / prms->a;
	t = (-prms->b - d_sqrt) * a_inv;
	if (t > RT_EPSILON && t < max_dist && range(prms->co_n + t * prms->d_n,
			0.0f, cone->height))
		return (true);
	t = (-prms->b + d_sqrt) * a_inv;
	if (t > RT_EPSILON && t < max_dist && range(prms->co_n + t * prms->d_n,
			0.0f, cone->height))
		return (true);
	return (false);
}

static inline bool	intersect_disk(const t_object *cone, t_params *prms,
		float max_dist)
{
	float	t;
	float	d_n_inv;

	d_n_inv = 1.0f / prms->d_n;
	t = (-prms->co_n + cone->height) * d_n_inv;
	if (t > RT_EPSILON && t < max_dist && (prms->a * t + 2.0f * prms->b) * t
		+ prms->c <= 0.0f)
		return (true);
	return (false);
}

bool	intersect_cone_fast(t_ray ray, const t_object *cone, float max_dist)
{
	t_params	params;

	params.d_n = v_dot(ray.dir, cone->normal);
	params.co = v_sub(ray.origin, cone->center);
	params.co_n = v_dot(params.co, cone->normal);
	if (intersect_surface(ray, cone, &params, max_dist))
		return (true);
	if (equal(params.d_n, 0.0f))
		return (false);
	return (intersect_disk(cone, &params, max_dist));
}
