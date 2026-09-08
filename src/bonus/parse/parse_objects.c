/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:19:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 11:27:15 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_float.h"
#include "ft_string.h"
#include "ft_vector.h"
#include "minirt.h"

static inline t_object_type	get_type(const t_vector *tokens)
{
	const char	*type;

	type = *(const char **)vector_get(tokens, 0);
	if (ft_strcmp(type, "cy") == 0)
		return (OBJ_CYLINDER);
	else
		return (OBJ_CONE);
}

static inline void	post_process(t_object *obj)
{
	float	k;

	obj->radius *= 0.5f;
	if (obj->type == OBJ_CYLINDER)
	{
		obj->height *= 0.5f;
		obj->r_2 = obj->radius * obj->radius;
	}
	else
	{
		k = obj->radius / obj->height;
		obj->r_2 = 1 + k * k;
	}
}

t_error	parse_sphere(const t_vector *tokens, t_minirt *minirt)
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
	if (ft_safe_atof(data[2], &sphere.radius))
		return (err_msg(ERR_PARSE, data[2]));
	sphere.radius *= 0.5f;
	err = parse_color(data[3], &sphere.color);
	if (err)
		return (err);
	return (vector_push(&minirt->objects, &sphere));
}

t_error	parse_plane(const t_vector *tokens, t_minirt *minirt)
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

t_error	parse_cylinder_cone(const t_vector *tokens, t_minirt *minirt)
{
	t_error		err;
	t_object	obj;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size != 6)
		return (err_msg(ERR_PARAMS, "Cylinder/Cone"));
	obj.type = get_type(tokens);
	data = (char **)tokens->data;
	err = parse_point(data[1], &obj.center);
	if (err)
		return (err);
	err = parse_vector(data[2], &obj.normal);
	if (err)
		return (err);
	if (ft_safe_atof(data[3], &obj.radius))
		return (err_msg(ERR_PARSE, data[3]));
	if (ft_safe_atof(data[4], &obj.height))
		return (err_msg(ERR_PARSE, data[4]));
	if (parse_color(data[5], &obj.color))
		return (ERR_PARSE);
	post_process(&obj);
	return (vector_push(&minirt->objects, &obj));
}
