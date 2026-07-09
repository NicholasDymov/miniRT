/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:55:51 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/09 21:33:21 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_string.h"
#include "ft_vector.h"
#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

int	vector_is_norm(t_vector3D *vec)
{
	float	length;

	if (vec->x > 1 || vec->y > 1 || vec->z > 1 || vec->x < -1 || vec->y < -1
		|| vec->z < -1)
		return (1);
	length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (length < 0.999f || length > 1.001f)
		return (1);
	return (0);
}

int	parse_color(char *str, uint32_t *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (!str || !color)
		return (1);
	rgb = ft_split(str, ',');
	if (!rgb)
		return (perror("malloc"), 1);
	if (ft_arrlen(rgb) != 3)
		return (ft_free_arr(rgb), 1);
	if (ft_check_int(rgb[0]) || ft_check_int(rgb[1]) || ft_check_int(rgb[2]))
		return (ft_free_arr(rgb), 1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_free_arr(rgb), 1);
	*color = (r << 16) | (g << 8) | b;
	ft_free_arr(rgb);
	return (0);
}

int	parse_xyz(char *str, t_point3D *xyz)
{
	char	**data;

	if (!str || !xyz)
		return (1);
	data = ft_split(str, ',');
	if (!data)
		return (perror("malloc"), 1);
	if (ft_arrlen(data) != 3)
		return (ft_free_arr(data), 1);
	if (ft_check_float(data[0]) || ft_check_float(data[1])
		|| ft_check_float(data[2]))
		return (ft_free_arr(data), 1);
	xyz->x = ft_atof(data[0]);
	xyz->y = ft_atof(data[1]);
	xyz->z = ft_atof(data[2]);
	ft_free_arr(data);
	return (0);
}

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

static void	free_ptr(void *ptr)
{
	free(*(void **)ptr);
}

static t_error	parse_line(char *line, t_minirt *minirt, t_parse_flags *flags)
{
	t_vector	tokens;
	char		*type;
	int			ret;

	if (ft_split(line, ' ', &tokens))
		return (perror("malloc"), ERR_NOMEM);
	type = (char *)vector_get(&tokens, 0);
	if (ft_strcmp(type, "A") == 0)
		ret = parse_ambient(tokens, minirt, &flags->ambient);
	else if (ft_strcmp(type, "C") == 0)
		ret = parse_camera(tokens, minirt, &flags->camera);
	else if (ft_strcmp(type, "L") == 0)
		ret = parse_light(tokens, minirt, &flags->light);
	else if (ft_strcmp(type, "sp") == 0)
		ret = parse_sphere(tokens, minirt);
	else if (ft_strcmp(type, "pl") == 0)
		ret = parse_plane(tokens, minirt);
	else if (ft_strcmp(type, "cy") == 0)
		ret = parse_cylinder(tokens, minirt);
	else
		ret = err_msg(ERR_TYPE, type);
	return (vector_destroy(&tokens, free_ptr), ret);
}

t_error	minirt_parse(int fd, t_minirt *minirt)
{
	char			*line;
	t_parse_flags	flags;

	line = get_next_line(fd);
	flags = (t_parse_flags){0};
	while (line)
	{
		if (ft_strlen(line) && parse_line(line, minirt, &flags))
			return (free(line), ERR_PARSE);
		free(line);
		line = get_next_line(fd);
	}
	if (!flags.ambient)
		return (err_msg(ERR_NO_AMB, NULL));
	if (!flags.camera)
		return (err_msg(ERR_NO_CAM, NULL));
	if (!flags.light)
		return (err_msg(ERR_NO_LIGHT, NULL));
	return (OK);
}
