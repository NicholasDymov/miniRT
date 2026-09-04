/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:23:28 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 14:06:16 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdbool.h>

bool	equal(float x, float y)
{
	if (x == y)
		return (true);
	if (fabsf(x - y) < FT_EPSILON)
		return (true);
	return (fabsf(x - y) < fmaxf(fabsf(x), fabsf(y)) * FT_EPSILON);
}

bool	range(float x, float start, float stop)
{
	return (start <= x && x <= stop);
}

float	square(float x)
{
	return (x * x);
}

float	pow32(float x)
{
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	return (x * x);
}
