/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:23:28 by ndymov            #+#    #+#             */
/*   Updated: 2026/08/25 12:58:35 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdbool.h>

float	square(float x)
{
	return (x * x);
}

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
