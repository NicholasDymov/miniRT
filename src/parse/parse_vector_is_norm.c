/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector_is_norm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 11:36:26 by ddymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:41:03 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	vector_is_norm(t_vector3D *vec)
{
	float	length;

	if (vec->x > 1 || vec->y > 1 || vec->z > 1
		|| vec->x < -1 || vec->y < -1 || vec->z < -1)
		return (1);
	length = sqrt(vec->x * vec->x + vec->y * vec->y
			+ vec->z * vec->z);
	if (length < 0.999f || length > 1.001f)
		return (1);
	return (0);
}
