/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 10:59:48 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 09:49:28 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_math.h"
#include "minirt.h"
#include <math.h>
#include <stdint.h>

uint32_t	rgba_pack(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
		return ((r << 24) | (g << 16) | (b << 8) | a);
	else
		return ((a << 24) | (b << 16) | (g << 8) | r);
}

uint32_t	color_checker(float u, float v, uint32_t color1, uint32_t color2)
{
	if (((int)floorf(u) + (int)floorf(v)) & 1)
		return (color2);
	else
		return (color1);
}

t_vector3d	color_bump(float u, float v, t_vector3d normal,
		mlx_texture_t *bump_map)
{
	t_vector3d	t;
	t_vector3d	n;
	uint32_t	x;
	uint32_t	y;
	size_t		i;

	u -= floorf(u);
	v -= floorf(v);
	x = (uint32_t)(u * (bump_map->width - 1));
	y = (uint32_t)(v * (bump_map->height - 1));
	i = ((size_t)y * bump_map->width + x) * 4;
	n.x = bump_map->pixels[i] * (2.0f / 255.0f) - 1.0f;
	n.y = bump_map->pixels[i + 1] * (2.0f / 255.0f) - 1.0f;
	n.z = bump_map->pixels[i + 2] * (2.0f / 255.0f) - 1.0f;
	t = v_orthonormal(normal);
	return (v_normalize(v_add(v_add(v_scale(n.x, t), v_scale(n.y,
						v_cross(normal, t))), v_scale(n.z, normal))));
}
