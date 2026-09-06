/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 10:59:48 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 10:25:12 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdint.h>

uint32_t	rgba_pack(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
		return ((r << 24) | (g << 16) | (b << 8) | a);
	else
		return ((a << 24) | (b << 16) | (g << 8) | r);
}
