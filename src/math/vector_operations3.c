/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 07:37:24 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 13:43:57 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdbool.h>

t_vector3d	v_project(t_vector3d a, t_vector3d n)
{
	return (v_sub(a, v_scale(v_dot(a, n), n)));
}

t_vector3d	v_reflect(t_vector3d i, t_vector3d n)
{
	return (v_sub(v_scale(2.0f * v_dot(i, n), n), i));
}
