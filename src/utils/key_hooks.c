/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 15:28:44 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/05 16:52:23 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"

void	minirt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(minirt->mlx);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
	{
		if (minirt->selected > 0)
			minirt->selected = 0;
		else if (minirt->selected == 0)
			minirt->selected = -1;
		else
			minirt->selected = 0;
		minirt_render(minirt);
	}
}
