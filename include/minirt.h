/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:35:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/07/01 16:28:46 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "ft_math.h"
# include "ft_vector.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

# define NO_FILE_ERR_MSG "You must provide scene description in a .rt file"

typedef struct s_ambient
{
	float		ratio;
	uint32_t	color;
}				t_ambient;

typedef struct s_camera
{
	t_point3D	position;
	t_vector3D	orientation;
	uint8_t		FOV;
}				t_camera;

typedef struct s_light
{
	t_point3D	position;
	float		brightness;
	uint32_t	color;
}				t_light;

typedef struct s_sphere
{
	t_point3D	center;
	float		diameter;
	uint32_t	color;
}				t_sphere;

typedef struct s_plane
{
	t_point3D	point;
	t_vector3D	normal;
	uint32_t	color;
}				t_plane;

typedef struct s_cylinder
{
	t_point3D	center;
	t_vector3D	normal;
	float		diameter;
	float		height;
	uint32_t	color;
}				t_cylinder;

typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_ambient	ambient;
	t_camera	camera;
	t_vector	lights;
	t_vector	spheres;
	t_vector	planes;
	t_vector	cylinders;
}				t_minirt;

void			minirt_render(t_minirt *minirt);
int				minirt_parse(int fd, t_minirt *minirt);

void			print_error(const char *msg);
#endif
