/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:29:00 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/06 13:17:46 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static inline void	update_best_hit(t_hit *best_hit, t_hit hit, size_t i)
{
	if (hit.hit && hit.distance < best_hit->distance)
	{
		*best_hit = hit;
		best_hit->object_id = i + 1;
	}
}

t_ray	ray_generate(uint32_t x, uint32_t y, const t_minirt *minirt)
{
	float	px;
	float	py;
	t_ray	ray;

	px = (2.0f * (x + 0.5f) / RT_WIDTH - 1.0f) * minirt->viewport.scale;
	py = (1.0f - 2.0f * (y + 0.5f) / RT_HEIGHT) * minirt->viewport.aspect
		* minirt->viewport.scale;
	ray.origin = minirt->camera.position;
	ray.direction = v_normalize(v_add(v_add(v_scale(px, minirt->viewport.right),
					v_scale(py, minirt->viewport.up)),
				minirt->viewport.forward));
	return (ray);
}

t_hit	ray_trace(t_ray ray, const t_minirt *minirt)
{
	t_hit			best_hit;
	t_hit			hit;
	const t_object	*obj;
	size_t			i;

	best_hit.hit = false;
	best_hit.distance = INFINITY;
	i = 0;
	while (i < minirt->objects.size)
	{
		obj = (const t_object *)vector_get(&minirt->objects, i);
		if (obj->type == OBJ_SPHERE)
			hit = intersect_sphere(ray, obj);
		else if (obj->type == OBJ_PLANE)
			hit = intersect_plane(ray, obj);
		else if (obj->type == OBJ_CYLINDER)
			hit = intersect_cylinder(ray, obj);
		else if (obj->type == OBJ_CONE)
			hit = intersect_cone(ray, obj);
		update_best_hit(&best_hit, hit, i);
		i++;
	}
	return (best_hit);
}
