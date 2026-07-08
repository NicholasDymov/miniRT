/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:55:51 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/08 11:27:43 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	minirt_parse(int fd, t_minirt *minirt)
{
	char	*line;

	while (line = get_next_line(fd))
	{
		if (parse_line(line, minirt)) 
		{
			free(line);
			return (ERROR);
		}
		free(line);
	}	
	return (0);
}

int	parse_line(char *line, t_minirt *minirt)
{
	if (line_is_empty(line))
		return (0);
	if (line_starts(line, "A "))
		return (parse_ambient(line, minirt));
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

int	line_is_empty(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] != ' ' && line[x] != '\t' && line[x] != '\n')
			return (0);
		x++;
	}
	return (1);
}

int	line_starts(char *line, char *start)
{
	int	len;

	len = ft_strlen(start);
	if (ft_strncmp(line, start, len) == 0)
		return (1);
	else
		return (0);	
}
