/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:35:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/04 14:10:02 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "ft_error.h"
# include "ft_math.h"
# include "ft_vector.h"
# include <MLX42/MLX42.h>
# include <stdbool.h>
# include <stdint.h>

# ifndef WIDTH
#  define WIDTH 1200
# endif

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# ifndef FT_MANDATORY
#  define FT_MANDATORY 1
# endif

# ifndef FT_EPSILON
#  define FT_EPSILON 1e-3f
# endif

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
}					t_object_type;

typedef struct s_ambient
{
	float			ratio;
	uint32_t		color;
}					t_ambient;

typedef struct s_camera
{
	t_point3d		position;
	t_vector3d		orientation;
	uint8_t			fov;
}					t_camera;

typedef struct s_ray
{
	t_point3d		origin;
	t_vector3d		direction;
}					t_ray;

typedef struct s_hit
{
	bool			hit;
	float			distance;
	t_point3d		point;
	t_vector3d		normal;
	t_vector3d		camera;
	uint32_t		color;
}					t_hit;

typedef struct s_viewport
{
	float			scale;
	float			aspect;
	t_vector3d		forward;
	t_vector3d		up;
	t_vector3d		right;
}					t_viewport;

typedef struct s_light
{
	t_point3d		position;
	float			ratio;
	uint32_t		color;
}					t_light;

typedef struct s_object
{
	t_point3d		center;
	t_vector3d		normal;
	float			radius;
	float			height;
	uint32_t		color;
	t_object_type	type;
}					t_object;

typedef struct s_parse_flags
{
	bool			camera;
	bool			ambient;
	bool			light;
}					t_parse_flags;

typedef struct s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef struct s_minirt
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_ambient		ambient;
	t_camera		camera;
	t_vector		lights;
	t_viewport		viewport;
	t_vector		objects;
}					t_minirt;

void				minirt_render(t_minirt *minirt);
t_error				minirt_parse(int fd, t_minirt *minirt);

t_ray				ray_generate(uint32_t x, uint32_t y,
						const t_minirt *minirt);
t_hit				ray_trace(t_ray ray, const t_minirt *minirt);

t_hit				intersect_sphere(t_ray ray, const t_object *sphere);
t_hit				intersect_plane(t_ray ray, const t_object *plane);
t_hit				intersect_cylinder(t_ray ray, const t_object *cylinder);

uint32_t			color_get(t_hit hit, const t_minirt *minirt);
uint32_t			rgba_pack(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

t_error				parse_ambient(const t_vector *tokens, t_minirt *minirt,
						bool *flag);
t_error				parse_camera(const t_vector *tokens, t_minirt *minirt,
						bool *flag);
t_error				parse_light(const t_vector *tokens, t_minirt *minirt,
						bool *flag);

t_error				parse_sphere(const t_vector *tokens, t_minirt *minirt);
t_error				parse_plane(const t_vector *tokens, t_minirt *minirt);
t_error				parse_cylinder(const t_vector *tokens, t_minirt *minirt);

t_error				parse_color(const char *token, uint32_t *color);
t_error				parse_point(const char *token, t_point3d *point);
t_error				parse_vector(const char *token, t_vector3d *vec);

t_error				err_msg(t_error error, const char *message);

#endif
