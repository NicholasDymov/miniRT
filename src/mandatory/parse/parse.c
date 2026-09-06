/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:55:51 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/02 15:59:27 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_io.h"
#include "ft_string.h"
#include "ft_vector.h"
#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

static void	free_ptr(void *ptr)
{
	free(*(void **)ptr);
}

static t_error	parse_line(char *line, t_minirt *minirt, t_parse_flags *flags)
{
	t_vector	tokens;
	char		*type;
	t_error		err;

	if (ft_split_words(&tokens, line, ft_isspace, 6))
		return (perror("malloc"), ERR_NOMEM);
	if (tokens.size == 0)
		return (vector_destroy(&tokens, free_ptr), OK);
	type = *(char **)vector_get(&tokens, 0);
	if (ft_strcmp(type, "A") == 0)
		err = parse_ambient(&tokens, minirt, &flags->ambient);
	else if (ft_strcmp(type, "C") == 0)
		err = parse_camera(&tokens, minirt, &flags->camera);
	else if (ft_strcmp(type, "L") == 0)
		err = parse_light(&tokens, minirt, &flags->light);
	else if (ft_strcmp(type, "sp") == 0)
		err = parse_sphere(&tokens, minirt);
	else if (ft_strcmp(type, "pl") == 0)
		err = parse_plane(&tokens, minirt);
	else if (ft_strcmp(type, "cy") == 0)
		err = parse_cylinder(&tokens, minirt);
	else
		err = err_msg(ERR_TYPE, type);
	return (vector_destroy(&tokens, free_ptr), err);
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
