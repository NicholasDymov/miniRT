/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 10:16:46 by ddymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:41:13 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(char **tokens, t_minirt *minirt)
{
	float	ratio;

	if (ft_arrlen(tokens) != 3)
		return (print_error("Error\nInvalid number of arguments (amb)\n"), 1);
	if (ft_check_float(tokens[1]))
		return (print_error("Error\nInvalid ambient ratio format\n"), 1);
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0f || ratio > 1.0f)
		return (print_error("Error\nInvalid ambient ratio range"), 1);
	minirt->ambient.ratio = ratio;
	if (parse_color(tokens[2], &minirt->ambient.color))
		return (print_error("Error\nInvalid ambient color data"), 1);
	else
		return (0);
}

int	parse_camera(char **tokens, t_minirt *minirt)
{
	int	fov;

	if (ft_arrlen(tokens) != 4)
		return (print_error("Error\nInvalid number of arguments (cam)\n"), 1);
	if (parse_xyz(tokens[1], &minirt->camera.position))
		return (print_error("Error\nInvalid camera position data\n"), 1);
	if (parse_xyz(tokens[2], &minirt->camera.orientation))
		return (print_error("Error\nInvalid camera orientation data\n"), 1);
	if (vector_is_norm(&minirt->camera.orientation))
		return (print_error("Error\nVector for camera is not normalized\n"), 1);
	if (ft_check_int(tokens[3]))
		return (print_error("Error\nInvalid fov format\n"), 1);
	fov = ft_atoi(tokens[3]);
	if (fov < 0 || fov > 180)
		return (print_error("Error\nInvalid fov range\n"), 1);
	minirt->camera.fov = fov;
	return (0);
}

int	parse_light(char **tokens, t_minirt *minirt)
{
	float	brightness;

	if (ft_arrlen(tokens) != 4)
		return (print_error("Error\nInvalid number of arguments (light)\n"), 1);
	if (parse_xyz(tokens[1], &minirt->light.position))
		return (print_error("Error\nInvalid light position data\n"), 1);
	if (ft_check_float(tokens[2]))
		return (print_error("Error\nInvalid brightness format\n"), 1);
	brightness = ft_atof(tokens[2]);
	if (brightness < 0.0f || brightness > 1.0f)
		return (print_error("Error\nInvalid brightness range"), 1);
	minirt->light.brightness = brightness;
	if (parse_color(tokens[3], &minirt->light.color))
		return (print_error("Error\nInvalid light color data"), 1);
	else
		return (0);
}
