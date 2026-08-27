/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:23:32 by ndymov            #+#    #+#             */
/*   Updated: 2026/08/26 17:56:32 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "minirt.h"
#include <math.h>

static t_hit	hit_build(t_ray ray, const t_object *object, float t)
{
	t_hit	hit;

	hit.hit = true;
	hit.distance = t;
	hit.point = v_add(ray.origin, v_scale(t, ray.direction));
	if (object->type == OBJ_SPHERE)
		hit.normal = v_normalize(v_sub(hit.point, object->center));
	else if (object->type == OBJ_PLANE || object->type == OBJ_DISK)
		hit.normal = object->normal;
	else if (object->type == OBJ_CYLINDER)
		hit.normal = v_normalize(v_project(v_sub(hit.point, object->center),
					object->normal));
	hit.color = object->color;
	return (hit);
}

static inline t_roots	solve_quadratic(float a, float b, float c)
{
	float	d;
	float	d_sqrt;
	float	a_inv;

	if (a < FT_EPSILON)
		return ((t_roots){.count = 0});
	d = b * b - a * c;
	if (d < 0.0f)
		return ((t_roots){.count = 0});
	d_sqrt = sqrtf(d);
	a_inv = 1.0f / a;
	return ((t_roots){.count = 2, .r1 = (-b - d_sqrt) * a_inv, .r2 = (-b
			+ d_sqrt) * a_inv});
}

static t_hit	intersect_sphere(t_ray ray, const t_object *sphere)
{
	t_vector3D	co;
	t_roots		roots;

	co = v_sub(ray.origin, sphere->center);
	roots = solve_quadratic(1.0f, v_dot(ray.direction, co), v_square(co)
			- square(sphere->radius));
	if (roots.count == 0)
		return ((t_hit){.hit = false});
	if (roots.r1 > FT_EPSILON)
		return (hit_build(ray, sphere, roots.r1));
	if (roots.r2 > FT_EPSILON)
		return (hit_build(ray, sphere, roots.r2));
	return ((t_hit){.hit = false});
}

static t_hit	intersect_plane(t_ray ray, const t_object *plane)
{
	float	t;
	float	numerator;
	float	denominator;
	t_hit	hit;

	denominator = v_dot(ray.direction, plane->normal);
	if (equal(denominator, 0.0f))
		return ((t_hit){.hit = false});
	numerator = v_dot(v_sub(plane->center, ray.origin), plane->normal);
	t = numerator / denominator;
	if (t <= FT_EPSILON)
		return ((t_hit){.hit = false});
	hit = hit_build(ray, plane, t);
	if (denominator > 0.0f)
		hit.normal = v_scale(-1.0f, hit.normal);
	return (hit);
}

static inline bool	height_constraint(float t, const t_object *cylinder,
		t_vector3D co, t_vector3D d)
{
	return (range(v_dot(v_add(co, v_scale(t, d)), cylinder->normal), -0.5f
			* cylinder->height, 0.5f * cylinder->height));
}

static t_hit	intersect_cylinder_surface(t_ray ray, const t_object *cylinder)
{
	t_vector3D	co;
	t_vector3D	co_;
	t_vector3D	d_;
	t_roots		roots;

	d_ = v_project(ray.direction, cylinder->normal);
	if (v_square(d_) < FT_EPSILON)
		return ((t_hit){.hit = false});
	co = v_sub(ray.origin, cylinder->center);
	co_ = v_project(co, cylinder->normal);
	roots = solve_quadratic(1 - square(v_dot(ray.direction, cylinder->normal)),
			v_dot(d_, co_), v_square(co_) - square(cylinder->radius));
	if (roots.count == 0)
		return ((t_hit){.hit = false});
	if (roots.r1 > FT_EPSILON && height_constraint(roots.r1, cylinder, co,
			ray.direction))
		return (hit_build(ray, cylinder, roots.r1));
	if (roots.r2 > FT_EPSILON && height_constraint(roots.r2, cylinder, co,
			ray.direction))
		return (hit_build(ray, cylinder, roots.r2));
	return ((t_hit){.hit = false});
}

static t_hit	intersect_disk(t_ray ray, const t_object *disk)
{
	t_hit	hit;

	hit = intersect_plane(ray, &(t_object){.type = OBJ_PLANE,
			.normal = disk->normal, .center = disk->center,
			.color = disk->color});
	if (!hit.hit)
		return (hit);
	if (v_square(v_sub(hit.point, disk->center)) > square(disk->radius))
		return ((t_hit){.hit = false});
	return (hit);
}

static t_hit	intersect_cylinder(t_ray ray, const t_object *cylinder)
{
	t_hit		hit;
	t_hit		hit_disk;
	t_object	disk;

	hit = intersect_cylinder_surface(ray, cylinder);
	disk.type = OBJ_DISK;
	disk.radius = cylinder->radius;
	disk.normal = cylinder->normal;
	disk.color = cylinder->color;
	disk.center = v_add(cylinder->center, v_scale(cylinder->height * 0.5f,
				cylinder->normal));
	hit_disk = intersect_disk(ray, &disk);
	if (hit_disk.hit && (!hit.hit || hit_disk.distance < hit.distance))
		hit = hit_disk;
	disk.center = v_add(cylinder->center, v_scale(cylinder->height * -0.5f,
				cylinder->normal));
	hit_disk = intersect_disk(ray, &disk);
	if (hit_disk.hit && (!hit.hit || hit_disk.distance < hit.distance))
		hit = hit_disk;
	return (hit);
}

t_hit	intersect(t_ray ray, const t_object *object)
{
	static const t_intersector intersectors[] = {
		[OBJ_SPHERE] = intersect_sphere,
		[OBJ_PLANE] = intersect_plane,
		[OBJ_CYLINDER] = intersect_cylinder,
	};
	return (intersectors[object->type](ray, object));
}
