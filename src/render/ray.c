/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:29:00 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/07 12:33:48 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_ray	ray_generate(uint32_t x, uint32_t y, t_minirt *minirt)
{
	float	px;
	float	py;
	t_ray	ray;

	px = (2.0f * (x + 0.5f) / WIDTH - 1.0f) * minirt->viewport.scale;
	py = (1.0f - 2.0f * (y + 0.5f) / HEIGHT) * minirt->viewport.aspect
		* minirt->viewport.scale;
	ray.origin = minirt->camera.position;
	ray.direction = v_normalize(v_add(v_add(v_scale(px, minirt->viewport.right),
					v_scale(py, minirt->viewport.up)),
				minirt->viewport.forward));
	return (ray);
}

static t_error	rt_callback(void *object, void *callback_data)
{
	t_rt_callback_data	*data;
	t_hit				hit;

	data = (t_rt_callback_data *)callback_data;
	hit = intersect(data->ray, (t_object *)object);
	if (hit.hit && hit.distance < data->hit.distance)
		data->hit.distance = hit.distance;
	return (OK);
}

t_hit	ray_trace(t_ray ray, t_minirt *minirt)
{
	t_rt_callback_data	data;

	data.ray = ray;
	data.hit.hit = false;
	data.hit.distance = INFINITY;
	vector_foreach(&minirt->objects, rt_callback, &data);
	return (data.hit);
}
