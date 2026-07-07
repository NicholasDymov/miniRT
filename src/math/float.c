/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:23:28 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/07 09:54:48 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdbool.h>

bool	f_equal(float x, float y)
{
	if (x == y)
		return (true);
	if (fabsf(x - y) < FT_EPSILON)
		return (true);
	return (fabsf(x - y) < fmaxf(fabsf(x), fabsf(y)) * FT_EPSILON);
}
