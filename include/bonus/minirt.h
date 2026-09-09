/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddymov <ddymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:35:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/09/09 08:42:30 by ndymov           ###   ########.fr       */
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

# ifndef RT_WIDTH
#  define RT_WIDTH 1200
# endif

# ifndef RT_HEIGHT
#  define RT_HEIGHT 800
# endif

# ifndef RT_EPSILON
#  define RT_EPSILON 1e-3f
# endif

# ifndef RT_THREADS
#  define RT_THREADS 8
# endif

# ifndef RT_TRANS_STEP
#  define RT_TRANS_STEP 3.0f
# endif

# ifndef RT_ROT_STEP
#  define RT_ROT_STEP 0.1f
# endif

# ifndef RT_RES_STEP
#  define RT_RES_STEP 0.2f
# endif

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
}					t_object_type;

typedef enum e_surface_type
{
	SURF_SOLID,
	SURF_CHECK,
	SURF_BUMP,
}					t_surface_type;

typedef struct s_ambient
{
	float			ratio;
	uint32_t		color;
}					t_ambient;

typedef struct s_camera
{
	t_point3d		position;
	t_vector3d		orientation;
	float			fov;
}					t_camera;

typedef struct s_ray
{
	t_point3d		origin;
	t_vector3d		dir;
}					t_ray;

typedef struct s_hit
{
	t_point3d		point;
	t_vector3d		normal;
	t_vector3d		camera;
	float			distance;
	uint32_t		object_id;
	uint32_t		color;
	bool			hit;
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
	mlx_texture_t	*bump_map;
	t_point3d		center;
	t_vector3d		normal;
	float			radius;
	float			radius_inv;
	float			height;
	float			height_inv;
	float			r_2;
	uint32_t		color;
	uint32_t		color_alt;
	t_object_type	type;
	t_surface_type	surface;
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
	t_vector		objects;
	t_vector		lights;
	t_ambient		ambient;
	t_camera		camera;
	t_viewport		viewport;
	int32_t			selected;
}					t_minirt;

void				minirt_render(t_minirt *minirt);
t_error				minirt_parse(int fd, t_minirt *minirt);

void				minirt_key_hook(mlx_key_data_t keydata, void *param);
void				minirt_mouse_hook(mouse_key_t mouse_key, action_t action,
						modifier_key_t mod, void *param);

t_ray				ray_generate(uint32_t x, uint32_t y,
						const t_minirt *minirt);
t_hit				ray_trace(t_ray ray, const t_minirt *minirt);

t_hit				intersect_plane(t_ray ray, const t_object *plane);
t_hit				intersect_sphere(t_ray ray, const t_object *sphere);
t_hit				intersect_cylinder(t_ray ray, const t_object *cylinder);
t_hit				intersect_cone(t_ray ray, const t_object *cone);

bool				intersect_plane_fast(t_ray ray, const t_object *plane,
						float max_dist);
bool				intersect_sphere_fast(t_ray ray, const t_object *sphere,
						float max_dist);
bool				intersect_cylinder_fast(t_ray ray, const t_object *cylinder,
						float max_dist);
bool				intersect_cone_fast(t_ray ray, const t_object *cone,
						float max_dist);

uint32_t			color_get(t_hit *hit, const t_minirt *minirt);
uint32_t			color_checker(float u, float v, uint32_t color1,
						uint32_t color2);
uint32_t			rgba_pack(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
t_vector3d			color_bump(float u, float v, t_vector3d normal,
						mlx_texture_t *bump_map);

t_error				parse_ambient(const t_vector *tokens, t_minirt *minirt,
						bool *flag);
t_error				parse_camera(const t_vector *tokens, t_minirt *minirt,
						bool *flag);
t_error				parse_light(const t_vector *tokens, t_minirt *minirt,
						bool *flag);

t_error				parse_sphere(const t_vector *tokens, t_minirt *minirt);
t_error				parse_plane(const t_vector *tokens, t_minirt *minirt);
t_error				parse_cylinder_cone(const t_vector *tokens,
						t_minirt *minirt);

t_error				parse_color(const char *token, uint32_t *color,
						bool verbose);
t_error				parse_point(const char *token, t_point3d *point);
t_error				parse_vector(const char *token, t_vector3d *vec);
t_error				parse_texture(const char *token, t_object *obj);

t_error				err_msg(t_error error, const char *message);

#endif
