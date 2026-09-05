/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 16:03:03 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/05 16:37:19 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "minirt.h"

void	minirt_mouse_hook(mouse_key_t mouse_key, action_t action,
		modifier_key_t mod, void *param)
{
	int32_t		x;
	int32_t		y;
	t_minirt	*minirt;
	t_ray		ray;
	t_hit		hit;

	if (mod)
		return ;
	minirt = (t_minirt *)param;
	if (mouse_key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(minirt->mlx, &x, &y);
		if (x < 0 || x >= RT_WIDTH || y < 0 || y >= RT_HEIGHT)
			return ;
		ray = ray_generate(x, y, minirt);
		hit = ray_trace(ray, minirt);
		if (hit.hit)
			minirt->selected = hit.object_id;
		else
			minirt->selected = 0;
		minirt_render(minirt);
	}
}
