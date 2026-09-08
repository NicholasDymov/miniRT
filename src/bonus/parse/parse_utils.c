/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:21:37 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/08 16:12:58 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_float.h"
#include "ft_int.h"
#include "ft_math.h"
#include "ft_string.h"
#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

static void	free_ptr(void *ptr)
{
	free(*(void **)ptr);
}

t_error	parse_color(const char *token, uint32_t *color, bool verbose)
{
	t_vector	rgb_vec;
	char		**data;
	int			rgb[3];
	t_error		err;

	if (token == NULL || color == NULL)
		return (ERR_INVAL);
	if (ft_split(&rgb_vec, token, ',', 3))
		return (perror("malloc"), ERR_NOMEM);
	err = OK;
	data = (char **)rgb_vec.data;
	if (rgb_vec.size != 3)
		err = ERR_PARSE;
	else if (ft_safe_atoi(data[0], &rgb[0]) || ft_safe_atoi(data[1], &rgb[1])
		|| ft_safe_atoi(data[2], &rgb[2]))
		err = ERR_PARSE;
	else if (!range(rgb[0], 0, 255) || !range(rgb[1], 0, 255) || !range(rgb[2],
			0, 255))
		err = ERR_RGB;
	else
		*color = rgba_pack(rgb[0], rgb[1], rgb[2], 255);
	if (verbose && err)
		(void)err_msg(err, token);
	return (vector_destroy(&rgb_vec, free_ptr), err);
}

t_error	parse_point(const char *token, t_point3d *pt)
{
	t_vector	coords;
	char		**data;
	t_error		err;

	if (token == NULL || pt == NULL)
		return (ERR_INVAL);
	if (ft_split(&coords, token, ',', 3))
		return (perror("malloc"), ERR_NOMEM);
	data = (char **)coords.data;
	if (coords.size != 3)
		err = err_msg(ERR_PARSE, token);
	else if (ft_safe_atof(data[0], &pt->x) || ft_safe_atof(data[1], &pt->y)
		|| ft_safe_atof(data[2], &pt->z))
		err = err_msg(ERR_PARSE, token);
	else
		err = OK;
	return (vector_destroy(&coords, free_ptr), err);
}

t_error	parse_vector(const char *token, t_vector3d *vec)
{
	t_vector	coords;
	char		**data;
	t_error		err;

	if (token == NULL || vec == NULL)
		return (ERR_INVAL);
	if (ft_split(&coords, token, ',', 3))
		return (perror("malloc"), ERR_NOMEM);
	data = (char **)coords.data;
	if (coords.size != 3)
		err = err_msg(ERR_PARSE, token);
	else if (ft_safe_atof(data[0], &vec->x) || ft_safe_atof(data[1], &vec->y)
		|| ft_safe_atof(data[2], &vec->z))
		err = err_msg(ERR_PARSE, token);
	else if (!range(vec->x, -1.0f, 1.0f) || !range(vec->y, -1.0f, 1.0f)
		|| !range(vec->z, -1.0f, 1.0f))
		err = err_msg(ERR_NORM, token);
	else if (!equal(v_square(*vec), 1.0f))
		err = err_msg(ERR_VEC, token);
	else
		err = OK;
	return (vector_destroy(&coords, free_ptr), err);
}

t_error	parse_texture(const char *token, t_object *obj)
{
	size_t	len;

	if (token == NULL || obj == NULL)
		return (ERR_INVAL);
	if (parse_color(token, &obj->color_alt, false) == OK)
		return (obj->surface = SURF_CHECK, OK);
	len = ft_strlen(token);
	if (len < 4 || ft_strcmp(token + len - 4, ".png") != 0)
		return (err_msg(ERR_PARSE, token));
	obj->bump_map = mlx_load_png(token);
	if (obj->bump_map == NULL)
		return (err_msg(ERR_PARSE, token));
	obj->surface = SURF_BUMP;
	return (OK);
}
