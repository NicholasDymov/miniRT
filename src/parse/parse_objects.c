/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:19:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/08/25 13:32:43 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_float.h"
#include "minirt.h"

t_error	parse_sphere(t_vector *tokens, t_minirt *minirt)
{
	t_error		err;
	t_object	sphere;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size != 4)
		return (err_msg(ERR_PARAMS, "Sphere"));
	sphere.type = OBJ_SPHERE;
	data = (char **)tokens->data;
	err = parse_point(data[1], &sphere.center);
	if (err)
		return (err);
	if (ft_safe_atof(data[2], &sphere.diameter))
		return (err_msg(ERR_PARSE, data[2]));
	sphere.radius = sphere.diameter * 0.5f;
	err = parse_color(data[3], &sphere.color);
	if (err)
		return (err);
	return (vector_push(&minirt->objects, &sphere));
}

t_error	parse_plane(t_vector *tokens, t_minirt *minirt)
{
	t_error		err;
	t_object	plane;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size != 4)
		return (err_msg(ERR_PARAMS, "Plane"));
	plane.type = OBJ_PLANE;
	data = (char **)tokens->data;
	err = parse_point(data[1], &plane.center);
	if (err)
		return (err);
	err = parse_vector(data[2], &plane.normal);
	if (err)
		return (err);
	err = parse_color(data[3], &plane.color);
	if (err)
		return (err);
	return (vector_push(&minirt->objects, &plane));
}

t_error	parse_cylinder(t_vector *tokens, t_minirt *minirt)
{
	t_error		err;
	t_object	cylinder;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size != 6)
		return (err_msg(ERR_PARAMS, "Cylinder"));
	cylinder.type = OBJ_CYLINDER;
	data = (char **)tokens->data;
	err = parse_point(data[1], &cylinder.center);
	if (err)
		return (err);
	err = parse_vector(data[2], &cylinder.normal);
	if (err)
		return (err);
	if (ft_safe_atof(data[3], &cylinder.diameter))
		return (err_msg(ERR_PARSE, data[3]));
	cylinder.radius = cylinder.diameter * 0.5f;
	if (ft_safe_atof(data[4], &cylinder.height))
		return (err_msg(ERR_PARSE, data[4]));
	err = parse_color(data[5], &cylinder.color);
	if (err)
		return (err);
	return (vector_push(&minirt->objects, &cylinder));
}
