/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:19:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 08:53:23 by ndymov           ###   ########.fr       */
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
	obj->radius_inv = 1.0f / obj->radius;
	if (obj->type == OBJ_CYLINDER)
	{
		obj->height *= 0.5f;
		obj->r_2 = obj->radius * obj->radius;
		obj->height_inv = 1.0f / obj->height;
	}
	else
	{
		k = obj->radius / obj->height;
		obj->r_2 = 1 + k * k;
		obj->height_inv = 1.0f / obj->height;
	}
}

t_error	parse_sphere(const t_vector *tokens, t_minirt *minirt)
{
	t_object	sphere;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size < 4 || tokens->size > 5)
		return (err_msg(ERR_PARAMS, "Sphere"));
	sphere = (t_object){0};
	sphere.type = OBJ_SPHERE;
	data = (char **)tokens->data;
	if (parse_point(data[1], &sphere.center))
		return (ERR_PARSE);
	if (ft_safe_atof(data[2], &sphere.radius))
		return (err_msg(ERR_PARSE, data[2]));
	sphere.radius *= 0.5f;
	sphere.radius_inv = 1.0f / sphere.radius;
	if (parse_color(data[3], &sphere.color, true))
		return (ERR_PARSE);
	if (tokens->size == 5 && parse_texture(data[4], &sphere))
		return (ERR_PARSE);
	return (vector_push(&minirt->objects, &sphere));
}

t_error	parse_plane(const t_vector *tokens, t_minirt *minirt)
{
	t_object	plane;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size < 4 || tokens->size > 5)
		return (err_msg(ERR_PARAMS, "Plane"));
	plane = (t_object){0};
	plane.type = OBJ_PLANE;
	data = (char **)tokens->data;
	if (parse_point(data[1], &plane.center))
		return (ERR_PARSE);
	if (parse_vector(data[2], &plane.normal))
		return (ERR_PARSE);
	if (parse_color(data[3], &plane.color, true))
		return (ERR_PARSE);
	if (tokens->size == 5 && parse_texture(data[4], &plane))
		return (ERR_PARSE);
	return (vector_push(&minirt->objects, &plane));
}

t_error	parse_cylinder_cone(const t_vector *tokens, t_minirt *minirt)
{
	t_object	obj;
	char		**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (tokens->size < 6 || tokens->size > 7)
		return (err_msg(ERR_PARAMS, "Cylinder/Cone"));
	obj = (t_object){0};
	obj.type = get_type(tokens);
	data = (char **)tokens->data;
	if (parse_point(data[1], &obj.center))
		return (ERR_PARSE);
	if (parse_vector(data[2], &obj.normal))
		return (ERR_PARSE);
	if (ft_safe_atof(data[3], &obj.radius))
		return (err_msg(ERR_PARSE, data[3]));
	if (ft_safe_atof(data[4], &obj.height))
		return (err_msg(ERR_PARSE, data[4]));
	if (parse_color(data[5], &obj.color, true))
		return (ERR_PARSE);
	if (tokens->size == 7 && parse_texture(data[6], &obj))
		return (ERR_PARSE);
	return (post_process(&obj), vector_push(&minirt->objects, &obj));
}
