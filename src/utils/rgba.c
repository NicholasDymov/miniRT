/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 10:59:48 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/07 11:16:44 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdint.h>

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
		return ((r << 24) | (g << 16) | (b << 8) | a);
	else
		return ((a << 24) | (b << 16) | (g << 8) | r);
}

uint32_t	get_color(t_hit hit, t_minirt *minirt)
{
	if (hit.hit)
		return (minirt->ambient.color);
	return (get_rgba(0, 0, 0, 255));
}
