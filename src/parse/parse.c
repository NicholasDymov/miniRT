/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:55:51 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:40:58 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_parse_flags
{
	bool	camera;
	bool	ambient;
	bool	light;
}			t_parse_flags;

int	minirt_parse(int fd, t_minirt *minirt)
{
	char			*line;
	t_parse_flags	flags;

	line = get_next_line(fd);
	flags = (t_parse_flags){0};
	while (line)
	{
		if (ft_strlen(line) && parse_line(line, minirt, &flags))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (flags.ambient && flags.camera && flags.light)
		return (0);
	print_error("Error\n");
	if (!flags.ambient)
		print_error("Element ambient is missing\n");
	if (!flags.camera)
		print_error("Element camera is missing\n");
	if (!flags.light)
		print_error("Element light is missing\n");
	return (1);
}

int	parse_line(char *line, t_minirt *minirt, t_parse_flags *flags)
{
	char	**tokens;
	int		ret;

	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		return (perror("malloc"), 1);
	if (ft_strcmp(tokens[0], "A") == 0 || ft_strcmp(tokens[0], "C") == 0
		|| ft_strcmp(tokens[0], "L") == 0)
		ret = parse_scene(tokens, minirt, flags);
	else if (ft_strcmp(tokens[0], "sp") == 0 || ft_strcmp(tokens[0], "pl") == 0
		|| ft_strcmp(tokens[0], "cy") == 0)
		ret = parse_objects(tokens, minirt);
	else
	{
		print_error("Error\nInvalid identifier\n");
		ret = 1;
	}
	ft_free_arr(tokens);
	return (ret);
}

int	parse_scene(char **tokens, t_minirt *minirt, t_parse_flags *flags)
{
	if (ft_strcmp(tokens[0], "A") == 0)
	{
		if (flags->ambient)
			return (print_error("Error\nExtra ambient identifier\n"), 1);
		flags->ambient = true;
		return (parse_ambient(tokens, minirt));
	}
	else if (ft_strcmp(tokens[0], "C") == 0)
	{
		if (flags->camera)
			return (print_error("Error\nExtra camera identifier\n"), 1);
		flags->camera = true;
		return (parse_camera(tokens, minirt));
	}
	else if (ft_strcmp(tokens[0], "L") == 0)
	{
		if (flags->light)
			return (print_error("Error\nExtra light identifier\n"), 1);
		flags->light = true;
		return (parse_light(tokens, minirt));
	}
	else
		return (1);
}

int	parse_objects(char **tokens, t_minirt *minirt)
{
	if (ft_strcmp(tokens[0], "sp") == 0)
		return (parse_sphere(tokens, minirt));
	else if (ft_strcmp(tokens[0], "pl") == 0)
		return (parse_plane(tokens, minirt));
	else if (ft_strcmp(tokens[0], "cy") == 0)
		return (parse_cylinder(tokens, minirt));
	else
		return (1);
}
