/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 15:28:44 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 14:05:39 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_math.h"
#include "ft_vector.h"
#include "minirt.h"
#include <math.h>

static inline void	hook_select(keys_t key, t_minirt *minirt)
{
	(void)key;
	if (minirt->selected > 0)
		minirt->selected = 0;
	else if (minirt->selected == 0)
		minirt->selected = -1;
	else
		minirt->selected = 0;
	minirt_render(minirt);
}

static inline void	hook_translate(keys_t key, t_minirt *minirt)
{
	t_point3d	*pos;

	if (minirt->selected == -1)
		pos = &minirt->light.position;
	else if (minirt->selected == 0)
		pos = &minirt->camera.position;
	else
		pos = &((t_object *)vector_get(&minirt->objects, minirt->selected
					- 1))->center;
	if (key == MLX_KEY_W)
		*pos = v_add(*pos, v_scale(RT_TRANS_STEP, minirt->viewport.forward));
	else if (key == MLX_KEY_S)
		*pos = v_sub(*pos, v_scale(RT_TRANS_STEP, minirt->viewport.forward));
	else if (key == MLX_KEY_D)
		*pos = v_add(*pos, v_scale(RT_TRANS_STEP, minirt->viewport.right));
	else if (key == MLX_KEY_A)
		*pos = v_sub(*pos, v_scale(RT_TRANS_STEP, minirt->viewport.right));
	else if (key == MLX_KEY_E)
		*pos = v_add(*pos, v_scale(RT_TRANS_STEP, minirt->viewport.up));
	else if (key == MLX_KEY_Q)
		*pos = v_sub(*pos, v_scale(RT_TRANS_STEP, minirt->viewport.up));
	else
		return ;
	minirt_render(minirt);
}

static inline void	hook_rotate(keys_t key, t_minirt *minirt)
{
	t_vector3d	*dir;
	t_object	*obj;
	t_vector3d	axis;

	if (minirt->selected < 0)
		return ;
	dir = &minirt->camera.orientation;
	axis = (t_vector3d){0.0f, 1.0f, 0.0f};
	if (minirt->selected > 0)
	{
		obj = ((t_object *)vector_get(&minirt->objects, minirt->selected - 1));
		if (obj->type == OBJ_SPHERE)
			return ;
		dir = &obj->normal;
		axis = minirt->viewport.forward;
	}
	if (key == MLX_KEY_W || key == MLX_KEY_S)
		axis = minirt->viewport.right;
	if (key == MLX_KEY_S || key == MLX_KEY_D)
		*dir = v_rotation(*dir, axis, RT_ROT_STEP);
	else if (key == MLX_KEY_W || key == MLX_KEY_A)
		*dir = v_rotation(*dir, axis, -RT_ROT_STEP);
	else
		return ;
	minirt_render(minirt);
}

static inline void	hook_resize(keys_t key, t_minirt *minirt)
{
	t_object	*obj;

	if (minirt->selected <= 0)
		return ;
	obj = ((t_object *)vector_get(&minirt->objects, minirt->selected - 1));
	if (obj->type == OBJ_PLANE)
		return ;
	if (key == MLX_KEY_D)
		obj->radius += RT_RES_STEP;
	else if (key == MLX_KEY_A)
		obj->radius = fmaxf(RT_EPSILON * 100.0f, obj->radius - RT_RES_STEP);
	else if (key == MLX_KEY_W && obj->type == OBJ_CYLINDER)
		obj->height += RT_RES_STEP;
	else if (key == MLX_KEY_S && obj->type == OBJ_CYLINDER)
		obj->height = fmaxf(RT_EPSILON * 100.0f, obj->height - RT_RES_STEP);
	else
		return ;
	minirt_render(minirt);
}

void	minirt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(minirt->mlx);
		return ;
	}
	if (keydata.key == MLX_KEY_TAB)
		hook_select(keydata.key, minirt);
	else if (keydata.modifier & MLX_CONTROL)
		hook_rotate(keydata.key, minirt);
	else if (keydata.modifier & MLX_ALT)
		hook_resize(keydata.key, minirt);
	else
		hook_translate(keydata.key, minirt);
}
