/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 17:48:53 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/06 09:54:03 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_vector.h"
#include "minirt.h"
#include <math.h>
#include <stddef.h>

static inline void	color_accumulate(t_color *color, float intensity,
		uint32_t rgba_light, uint32_t rgba_obj)
{
	const uint8_t	*obj = (const uint8_t *)&rgba_obj;
	const uint8_t	*light = (const uint8_t *)&rgba_light;

	color->r += intensity * obj[0] * light[0];
	color->g += intensity * obj[1] * light[1];
	color->b += intensity * obj[2] * light[2];
}

static inline uint32_t	color_clamp(t_color *color, uint32_t alpha)
{
	static const float	inv_255 = 1.0f / 255.0f;

	color->r = fminf(255.0f, color->r * inv_255);
	color->g = fminf(255.0f, color->g * inv_255);
	color->b = fminf(255.0f, color->b * inv_255);
	return (rgba_pack(color->r, color->g, color->b, alpha));
}

static inline bool	is_shadowed(t_ray ray, float max_dist,
		const t_minirt *minirt)
{
	t_hit			hit;
	const t_object	*obj;
	size_t			i;

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
		if (hit.hit && hit.distance < max_dist)
			return (true);
		i++;
	}
	return (false);
}

static inline void	phong_light(t_hit hit, t_light light, t_color *color,
		const t_minirt *minirt)
{
	t_ray	light_ray;
	float	light_distance;
	float	light_distance_inv;
	float	cosine;

	light_ray.direction = v_sub(light.position, hit.point);
	cosine = v_dot(hit.normal, light_ray.direction);
	if (cosine <= 0.0f)
		return ;
	light_ray.origin = hit.point;
	light_distance = v_length(light_ray.direction);
	light_distance_inv = 1.0f / light_distance;
	light_ray.direction = v_scale(light_distance_inv, light_ray.direction);
	cosine *= light_distance_inv;
	if (is_shadowed(light_ray, light_distance, minirt))
		return ;
	color_accumulate(color, light.ratio * cosine, 0xFFFFFFFF, hit.color);
}

uint32_t	color_get(t_hit hit, const t_minirt *minirt)
{
	t_color	color;

	color = (t_color){.r = 0.0f, .g = 0.0f, .b = 0.0f};
	hit.point = v_add(hit.point, v_scale(RT_EPSILON, hit.normal));
	color_accumulate(&color, 1.0f, minirt->ambient.color, hit.color);
	phong_light(hit, minirt->light, &color, minirt);
	if (minirt->selected == (int)hit.object_id)
		return (color_clamp(&color, 127));
	else
		return (color_clamp(&color, 255));
}
