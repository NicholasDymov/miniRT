/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 11:48:30 by ddymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:41:10 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(char **tokens, t_minirt *minirt)
{
	t_object	obj;

	obj = (t_object){0};
	if (ft_arrlen(tokens) != 4)
		return (print_error("Error\nInvalid number of arguments (sph)\n"), 1);
	obj.type = OBJ_SPHERE;
	if (parse_xyz(tokens[1], &obj.center))
		return (print_error("Error\nInvalid sphere center data\n"), 1);
	if (ft_check_float(tokens[2]))
		return (print_error("Error\nInvalid sphere diameter format\n"), 1);
	obj.diameter = ft_atof(tokens[2]);
	if (obj.diameter <= 0.0f)
		return (print_error("Error\nInvalid sphere diameter range\n"), 1);
	if (parse_color(tokens[3], &obj.color))
		return (print_error("Error\nInvalid sphere color data\n"), 1);
	else
		return (0);
}

int	parse_plane(char **tokens, t_minirt *minirt)
{
	t_object	obj;

	obj = (t_object){0};
	if (ft_arrlen(tokens) != 4)
		return (print_error("Error\nInvalid number of arguments (pl)\n"), 1);
	obj.type = OBJ_PLANE;
	if (parse_xyz(tokens[1], &obj.center))
		return (print_error("Error\nInvalid plane center data\n"), 1);
	if (parse_xyz(tokens[2], &obj.normal))
		return (print_error("Error\nInvalid plane vector data\n"), 1);
	if (vector_is_norm(&obj.normal))
		return (print_error("Error\nPlane vector is not normalized\n"), 1);
	if (parse_color(tokens[3], &obj.color))
		return (print_error("Error\nInvalid plane color data\n"), 1);
	else
		return (0);
}

int	parse_cylinder(char **tokens, t_minirt *minirt)
{
	t_object	obj;

	obj = (t_object){0};
	if (ft_arrlen(tokens) != 6)
		return (print_error("Error\nInvalid number of arguments (cyl)\n"), 1);
	obj.type = OBJ_CYLINDER;
	if (parse_xyz(tokens[1], &obj.center))
		return (print_error("Error\nInvalid cylinder center data\n"), 1);
	if (parse_xyz(tokens[2], &obj.normal))
		return (print_error("Error\nInvalid cylinder vector data\n"), 1);
	if (vector_is_norm(&obj.normal))
		return (print_error("Error\nCylinder vector is not normalized\n"), 1);
	if (ft_check_float(tokens[3]))
		return (print_error("Error\nInvalid cylinder diameter format\n"), 1);
	obj.diameter = ft_atof(tokens[3]);
	if (ft_check_float(tokens[4]))
		return (print_error("Error\nInvalid cylinder height format\n"), 1);
	obj.height = ft_atof(tokens[4]);
	if (obj.diameter <= 0.0f || obj.height <= 0.0f)
		return (print_error("Error\nInvalid cylinder diam/height range\n"), 1);
	if (parse_color(tokens[5], &obj.color))
		return (print_error("Error\nInvalid cylinder color data\n"), 1);
	else
		return (0);
}
