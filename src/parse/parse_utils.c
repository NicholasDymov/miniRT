/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:03:45 by ddymov            #+#    #+#             */
/*   Updated: 2026/07/09 12:41:07 by ddymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_check_int(char *str)
{
	int	x;

	if (!str || str[0] == '\0')
		return (1);
	x = 0;
	if (str[x] == '-' || str[x] == '+')
		x++;
	if (!str[x])
		return (1);
	while (str[x])
	{
		if (!ft_isdigit(str[x]))
			return (1);
		x++;
	}
	return (0);
}

int	ft_check_float(char *str)
{
	int	x;
	int	dot;
	int	digit;

	x = 0;
	dot = 0;
	digit = 0;
	if (!str || str[0] == '\0')
		return (1);
	if (str[x] == '-' || str[x] == '+')
		x++;
	if (!ft_isdigit(str[x]))
		return (1);
	while (str[x])
	{
		if (ft_isdigit(str[x]))
			digit = 1;
		else if (str[x] == '.' && !dot)
			dot = 1;
		else
			return (1);
		x++;
	}
	return (!digit);
}

int	ft_arrlen(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	ft_free_arr(char **arr)
{
	int	x;

	x = 0;
	if (!arr)
		return ;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}
