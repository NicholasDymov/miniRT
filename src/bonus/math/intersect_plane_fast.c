/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_fast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 18:04:41 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <threads.h>

bool	intersect_plane_fast(t_ray ray, const t_object *plane, float max_dist)
{
	float	t;
	float	numerator;
	float	denominator;

	denominator = v_dot(ray.dir, plane->normal);
	if (equal(denominator, 0.0f))
		return (false);
	numerator = v_dot(v_sub(plane->center, ray.origin), plane->normal);
	t = numerator / denominator;
	if (t <= RT_EPSILON || t > max_dist)
		return (false);
	return (true);
}
