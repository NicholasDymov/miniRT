/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xyz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 11:34:53 by ddymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:41:00 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
