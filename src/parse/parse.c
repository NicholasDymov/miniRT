/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:55:51 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/08 16:45:47 by ddymov           ###   ########.fr       */
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
	t_parse_flags	*flags;

	line = get_next_line(fd);
	flags = (t_parse_flags){0};
	while (line)
	{
		if (!(ft_strlen(line) == 0) && parse_line(line, minirt,
				&flags))
			return (free(line), ERROR);
		free(line);
		line = get_next_line(fd);
	}
	return (ft_check_for_flags(flags));
}

int	ft_check_for_flags(t_parse_flags *flags)
{
	if (flags->ambient == false)
		return (error("Element ambient is missing"));
	if (flags->camera == false)
		return (error("Element camera is missing"));
	if (flags->light == false)
		return (error("Element light is missing"));
	return (OK);
}

int	parse_line(char *line, t_minirt *minirt, t_parse_flags *flags)
{
	t_list	*tokens;
	int		ret;

	tokens = ft_split(line, ' ');
	if (tokens == NULL)
		return (error("Malloc"));
	if (ft_strcmp((char *)tokens->data, "A") == 0
		|| ft_strcmp((char *)tokens->data, "C") == 0
		|| ft_strcmp((char *)tokens->data, "L") == 0)
		ret = parse_scene(tokens, minirt, flags);
	else if (ft_strcmp((char *)tokens->data, "sp") == 0
		|| ft_strcmp((char *)tokens->data, "pl") == 0
		|| ft_strcmp((char *)tokens->data, "cy") == 0)
		ret = parse_objects(tokens, minirt, flags);
	else
		ret = error("Invalid identifier");
	ft_lstclear(&tokens, free);
	return (ret);
}

int	parse_scene(t_list *tokens, t_minirt *minirt, t_parse_flags *flags)
{
	if (ft_strcmp((char *)tokens->data, "A") == 0)
	{
		if (flags->ambient)
			return (error("Extra ambient identifier"));
		flags->ambient = true;
		return (parse_ambient(tokens->next, minirt));
	}
	else if (ft_strcmp((char *)tokens->data, "C") == 0)
	{
		if (flags->camera)
			return (error("Extra camera identifier"));
		flags->camera = true;
		return (parse_camera(tokens->next, minirt));
	}
	else if (ft_strcmp((char *)tokens->data, "L") == 0)
	{
		if (flags->light)
			return (error("Extra light identifier"));
		flags->light = true;
		return (parse_light(tokens->next, minirt));
	}
	else
		return (ERROR);
}

int	parse_objects(t_list *tokens, t_minirt *minirt)
{
	if (ft_strcmp((char *)tokens->data, "sp") == 0)
		return (parse_sphere(tokens->next, minirt));
	else if (ft_strcmp((char *)tokens->data, "pl") == 0)
		return (parse_plane(tokens->next, minirt));
	else if (ft_strcmp((char *)tokens->data, "cy") == 0)
		return (parse_cylinder(tokens->next, minirt));
	else
		return (ERROR);
}

int	parse_ambient(t_list *tokens, t_minirt *minirt)
{
	float	ratio;

	if (!tokens || !tokens->next)
		return (error("Not enough information about ambient element"));
	ratio = atof((char *)tokens->data);
	if (ratio < 0.0f || ratio > 1.0f)
		return (error("Invalid range for ambient ratio"));
	minirt->ambient.ratio = ratio;
	if (parse_color((char *)tokens->next->data, &minirt->ambient.color))
		return (ERROR);
	else
		return (OK);
}

int	parse_color(char *str, uint32_t *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (!str)
		return (error("No arguments for color"));
	rgb = ft_split(str, ',');
	if (!rgb)
		return (error("Malloc"));
	if (ft_arrlen(rgb) != 3)
		return (free_arr(rgb), error("Invalid number of arguments of color"));
	if (ft_check_for_digits(rgb))
		return (error("Invalid format for arguments of color"));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_arr(rgb), error("Invalid range for arguments of color"));
	*color = (r << 16) | (g << 8) | b;
	free_arr(rgb);
	return (OK);
}

int ft_arrlen(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	free_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}

int	error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (ERROR);
}

int	ft_check_for_int(char **arr)
{
	int	x;
	int	y;

	x = 0;
	while (arr[x])
	{
		if (arr[x][0] == '\0')
			return (ERROR);
		y = 0;
		while (arr[x][y])
		{
			if (!ft_isdigit(arr[x][y]))
				return (ERROR);
			y++;
		}
		x++;
	}
	return (OK);
}
