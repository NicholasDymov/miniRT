/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 13:19:34 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 10:23:02 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_vector.h"
#include "minirt.h"
#include <MLX42/MLX42.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static t_error	minirt_init(t_minirt *minirt)
{
	minirt->objects.data = NULL;
	minirt->mlx = NULL;
	if (vector_init(&minirt->objects, sizeof(t_object), 4))
		return (perror("malloc"), ERR_NOMEM);
	if (vector_init(&minirt->lights, sizeof(t_light), 1))
		return (perror("malloc"), ERR_NOMEM);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	if (minirt->mlx == NULL)
		return (err_msg(ERR_MLX, mlx_strerror(mlx_errno)));
	minirt->image = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (minirt->image == NULL || mlx_image_to_window(minirt->mlx, minirt->image,
			0, 0) == -1)
	{
		mlx_close_window(minirt->mlx);
		return (err_msg(ERR_MLX, mlx_strerror(mlx_errno)));
	}
	return (0);
}

static void	minirt_destroy(t_minirt *minirt)
{
	if (minirt->mlx != NULL)
		mlx_terminate(minirt->mlx);
	vector_destroy(&minirt->objects, NULL);
	vector_destroy(&minirt->lights, NULL);
}

static void	mlx_esc_hook(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_minirt	minirt;

	if (argc < 2)
		return (err_msg(ERR_NO_FILE, NULL), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror(argv[1]), EXIT_FAILURE);
	if (minirt_init(&minirt) || minirt_parse(fd, &minirt))
	{
		minirt_destroy(&minirt);
		return (close(fd), EXIT_FAILURE);
	}
	(void)close(fd);
	minirt_render(&minirt);
	mlx_loop_hook(minirt.mlx, mlx_esc_hook, minirt.mlx);
	mlx_loop(minirt.mlx);
	minirt_destroy(&minirt);
	return (EXIT_SUCCESS);
}
