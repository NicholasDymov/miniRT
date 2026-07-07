/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/07 12:27:48 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit	intersect_sphere(t_ray ray, t_object *object)
{
	(void)ray;
	(void)object;
	return ((t_hit){0});
}

static t_hit	intersect_plane(t_ray ray, t_object *object)
{
	(void)ray;
	(void)object;
	return ((t_hit){0});
}
static t_hit	intersect_cylinder(t_ray ray, t_object *object)
{
	(void)ray;
	(void)object;
	return ((t_hit){0});
}

t_hit	intersect(t_ray ray, t_object *object)
{
	static const t_intersector intersectors[] = {
		[OBJ_SPHERE] = intersect_sphere,
		[OBJ_PLANE] = intersect_plane,
		[OBJ_CYLINDER] = intersect_cylinder,
	};
	return (intersectors[object->type](ray, object));
}
