/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:55:51 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/08 12:45:47 by ndymov           ###   ########.fr       */
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
		if (!(ft_strlen(line) == 1 && *line == '\n') && parse_line(line, minirt,
				&flags))
			return (free(line), ERROR);
		free(line);
		line = get_next_line(fd);
	}
	return (!(flags.camera && flags.ambient && flags.light));
}

int	parse_line(char *line, t_minirt *minirt, t_parse_flags *flags)
{
	t_list	*tokens;

	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		return (perror("malloc"), 1);
	if (ft_strcmp((char *)tokens->data, "A"))
	{
		if (flags->ambient)
			return (1);
		flags->ambient = true;
		return (parse_ambient(tokens->next, minirt));
	}
	if (line_starts(line, "C "))
		return (parse_camera(line, minirt));
	if (line_starts(line, "L "))
		return (parse_light(line, minirt));
	if (line_starts(line, "sp "))
		return (parse_sphere(line, minirt));
	if (line_starts(line, "pl "))
		return (parse_plane(line, minirt));
	if (line_starts(line, "cy "))
		return (parse_cylinder(line, minirt));
	return (1);
}
