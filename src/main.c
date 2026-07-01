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
	minirt->lights.data = NULL;
	minirt->spheres.data = NULL;
	minirt->planes.data = NULL;
	minirt->cylinders.data = NULL;
	minirt->mlx = NULL;
	if (vector_init(&minirt->lights, sizeof(t_light), 1))
		return (perror("malloc"), 1);
	if (vector_init(&minirt->spheres, sizeof(t_sphere), 1))
		return (perror("malloc"), 1);
	if (vector_init(&minirt->planes, sizeof(t_plane), 1))
		return (perror("malloc"), 1);
	if (vector_init(&minirt->cylinders, sizeof(t_cylinder), 1))
		return (perror("malloc"), 1);
	minirt->mlx = mlx_init(128, 128, "miniRT", 1);
	if (minirt->mlx == NULL)
		return (print_error(mlx_strerror(mlx_errno)), 1);
	minirt->image = mlx_new_image(minirt->mlx, 128, 128);
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
	vector_destroy(&minirt->lights);
	vector_destroy(&minirt->spheres);
	vector_destroy(&minirt->planes);
	vector_destroy(&minirt->cylinders);
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
	minirt_render(&minirt);
	mlx_loop_hook(minirt.mlx, mlx_esc_hook, minirt.mlx);
	mlx_loop(minirt.mlx);
	(void)close(fd);
	minirt_destroy(&minirt);
	return (EXIT_SUCCESS);
}
