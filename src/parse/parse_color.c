/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:05:34 by ddymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:41:16 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
