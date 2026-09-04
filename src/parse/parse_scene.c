/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 15:20:33 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 14:34:08 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_float.h"
#include "ft_int.h"
#include "minirt.h"

t_error	parse_ambient(const t_vector *tokens, t_minirt *minirt, bool *flag)
{
	char	**data;
	t_error	err;
	uint8_t	*rgba;

	if (tokens == NULL || minirt == NULL || flag == NULL)
		return (ERR_INVAL);
	if (*flag)
		return (err_msg(ERR_EXTRA_AMB, NULL));
	*flag = true;
	if (tokens->size != 3)
		return (err_msg(ERR_PARAMS, "Ambient light"));
	data = (char **)tokens->data;
	if (ft_safe_atof(data[1], &minirt->ambient.ratio))
		return (err_msg(ERR_PARSE, data[1]));
	if (!range(minirt->ambient.ratio, 0.0f, 1.0f))
		return (err_msg(ERR_AMB, NULL));
	err = parse_color(data[2], &minirt->ambient.color);
	if (err)
		return (err);
	rgba = (uint8_t *)&minirt->ambient.color;
	minirt->ambient.color = rgba_pack(rgba[0] * minirt->ambient.ratio, rgba[1]
			* minirt->ambient.ratio, rgba[2] * minirt->ambient.ratio, 255);
	return (OK);
}

t_error	parse_camera(const t_vector *tokens, t_minirt *minirt, bool *flag)
{
	t_error	err;
	int		fov;
	char	**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (*flag)
		return (err_msg(ERR_EXTRA_CAM, NULL));
	*flag = true;
	if (tokens->size != 4)
		return (err_msg(ERR_PARAMS, "Camera"));
	data = (char **)tokens->data;
	err = parse_point(data[1], &minirt->camera.position);
	if (err)
		return (err);
	err = parse_vector(data[2], &minirt->camera.orientation);
	if (err)
		return (err);
	if (ft_safe_atoi(data[3], &fov))
		return (err_msg(ERR_PARSE, data[3]));
	if (!range(fov, 1, 179))
		return (err_msg(ERR_FOV, data[3]));
	minirt->camera.fov = fov;
	return (OK);
}

t_error	parse_light(const t_vector *tokens, t_minirt *minirt, bool *flag)
{
	t_error	err;
	t_light	light;
	char	**data;

	if (tokens == NULL || minirt == NULL)
		return (ERR_INVAL);
	if (FT_MANDATORY && *flag)
		return (err_msg(ERR_EXTRA_LIGHT, NULL));
	*flag = true;
	if (tokens->size != 4)
		return (err_msg(ERR_PARAMS, "Light"));
	data = (char **)tokens->data;
	err = parse_point(data[1], &light.position);
	if (err)
		return (err);
	if (ft_safe_atof(data[2], &light.ratio))
		return (err_msg(ERR_PARSE, data[2]));
	if (!range(light.ratio, 0.0f, 1.0f))
		return (err_msg(ERR_LIGHT, NULL));
	err = parse_color(data[3], &light.color);
	if (err)
		return (err);
	return (vector_push(&minirt->lights, &light));
}
