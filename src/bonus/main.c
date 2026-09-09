/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:19:34 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 09:39:06 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_string.h"
#include "ft_vector.h"
#include "minirt.h"
#include <MLX42/MLX42.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	object_destroy(void *ptr)
{
	t_object	*obj;

	obj = (t_object *)ptr;
	if (obj->surface == SURF_BUMP)
		mlx_delete_texture(obj->bump_map);
}

static t_error	minirt_init(t_minirt *minirt)
{
	minirt->objects.data = NULL;
	minirt->lights.data = NULL;
	minirt->mlx = NULL;
	if (vector_init(&minirt->objects, sizeof(t_object), 4))
		return (perror("malloc"), ERR_NOMEM);
	if (vector_init(&minirt->lights, sizeof(t_light), 1))
		return (perror("malloc"), ERR_NOMEM);
	minirt->mlx = mlx_init(RT_WIDTH, RT_HEIGHT, "miniRT", 0);
	if (minirt->mlx == NULL)
		return (err_msg(ERR_MLX, mlx_strerror(mlx_errno)));
	minirt->image = mlx_new_image(minirt->mlx, RT_WIDTH, RT_HEIGHT);
	if (minirt->image == NULL || mlx_image_to_window(minirt->mlx, minirt->image,
			0, 0) == -1)
	{
		mlx_close_window(minirt->mlx);
		return (err_msg(ERR_MLX, mlx_strerror(mlx_errno)));
	}
	minirt->selected = 0;
	return (0);
}

static void	minirt_destroy(t_minirt *minirt)
{
	vector_destroy(&minirt->objects, object_destroy);
	if (minirt->mlx != NULL)
		mlx_terminate(minirt->mlx);
	vector_destroy(&minirt->lights, NULL);
}

static bool	filename_valid(const char *filename)
{
	size_t	len;

	if (filename == NULL)
		return (false);
	len = ft_strlen(filename);
	if (len < 4 || filename[len - 4] == '/')
		return (false);
	if (ft_strcmp(filename + len - 3, ".rt") != 0)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_minirt	minirt;

	if (argc != 2 || !filename_valid(argv[1]))
		return (err_msg(ERR_ARG, NULL), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 && err_msg(ERR_MAX, NULL))
		return (perror(argv[1]), EXIT_FAILURE);
	if (minirt_init(&minirt) || minirt_parse(fd, &minirt))
	{
		minirt_destroy(&minirt);
		return (close(fd), EXIT_FAILURE);
	}
	(void)close(fd);
	minirt_render(&minirt);
	mlx_key_hook(minirt.mlx, minirt_key_hook, &minirt);
	mlx_mouse_hook(minirt.mlx, minirt_mouse_hook, &minirt);
	mlx_loop(minirt.mlx);
	minirt_destroy(&minirt);
	return (EXIT_SUCCESS);
}
