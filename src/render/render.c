/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:04:08 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/07 12:48:33 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

void	viewport_init(t_minirt *minirt)
{
	float		fov;
	t_vector3D	up;
	t_vector3D	down;
	t_viewport	viewport;

	fov = minirt->camera.FOV;
	viewport.scale = tanf(fov * (float)M_PI / 360.0f);
	viewport.aspect = (float)HEIGHT / WIDTH;
	viewport.forward = minirt->camera.orientation;
	up = (t_vector3D){0.0f, 1.0f, 0.0f};
	down = (t_vector3D){0.0f, -1.0f, 0.0f};
	if (v_equal(viewport.forward, up))
		viewport.right = (t_vector3D){0.0f, 0.0f, 1.0f};
	else if (v_equal(viewport.forward, down))
		viewport.right = (t_vector3D){0.0f, 0.0f, -1.0f};
	else
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
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			ray = ray_generate(x, y, minirt);
			hit = ray_trace(ray, minirt);
			pixels[y * WIDTH + x] = get_color(hit, minirt);
			y++;
		}
		x++;
	}
}
