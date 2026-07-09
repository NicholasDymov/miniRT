// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "ft_vector.h"
#include "minirt.h"
#include <MLX42/MLX42.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	minirt_init(t_minirt *minirt)
{
	minirt->objects.data = NULL;
	minirt->mlx = NULL;
	if (vector_init(&minirt->objects, sizeof(t_object), 1))
		return (perror("malloc"), 1);
	minirt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	if (minirt->mlx == NULL)
		return (print_error(mlx_strerror(mlx_errno)), 1);
	minirt->image = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (minirt->image == NULL || mlx_image_to_window(minirt->mlx, minirt->image,
			0, 0) == -1)
	{
		mlx_close_window(minirt->mlx);
		return (print_error(mlx_strerror(mlx_errno)), 1);
	}
	return (0);
}

static void	minirt_destroy(t_minirt *minirt)
{
	if (minirt->mlx != NULL)
		mlx_terminate(minirt->mlx);
	vector_destroy(&minirt->objects);
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
		return (print_error(NO_FILE_ERR_MSG), EXIT_FAILURE);
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
