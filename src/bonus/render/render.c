/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:04:08 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 14:10:38 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

static inline t_vector3d	pitch_clamp(t_vector3d *forward)
{
	float		scale;
	t_vector3d	hor;
	const float	threshold = RT_EPSILON * 10.0f;

	if (fabsf(forward->y) + threshold < 1.0f)
		return (*forward);
	scale = sqrtf(1.0f - square(1.0f - threshold));
	hor = v_normalize((t_vector3d){forward->x, 0.0f, forward->z});
	if (v_square(hor) == 0.0f)
		hor = (t_vector3d){0.0f, 0.0f, 1.0f};
	forward->x = hor.x * scale;
	forward->z = hor.z * scale;
	if (forward->y > 0.0f)
		forward->y = 1.0f - threshold;
	else
		forward->y = -1.0f + threshold;
	return (*forward);
}

void	viewport_init(t_minirt *minirt)
{
	t_vector3d	up;
	t_viewport	viewport;

	viewport.scale = tanf(minirt->camera.fov * (float)M_PI / 360.0f);
	viewport.aspect = (float)RT_HEIGHT / RT_WIDTH;
	viewport.forward = pitch_clamp(&minirt->camera.orientation);
	up = (t_vector3d){0.0f, 1.0f, 0.0f};
	viewport.right = v_normalize(v_cross(up, viewport.forward));
	viewport.up = v_cross(viewport.forward, viewport.right);
	minirt->viewport = viewport;
}

void	minirt_render(t_minirt *minirt)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	t_hit		hit;
	uint32_t	*pixels;

	viewport_init(minirt);
	pixels = (uint32_t *)minirt->image->pixels;
	y = 0;
	while (y < RT_HEIGHT)
	{
		x = 0;
		while (x < RT_WIDTH)
		{
			ray = ray_generate(x, y, minirt);
			hit = ray_trace(ray, minirt);
			if (hit.hit)
				pixels[y * RT_WIDTH + x] = color_get(&hit, minirt);
			else
				pixels[y * RT_WIDTH + x] = rgba_pack(0, 0, 0, 255);
			x++;
		}
		y++;
	}
}
