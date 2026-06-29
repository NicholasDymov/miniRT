/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndymov <ndymov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 15:35:17 by ndymov            #+#    #+#             */
/*   Updated: 2026/06/29 16:10:48 by ndymov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "math.h"
# include <stdint.h>

typedef enum e_object_type
{
	OBJ_AMBIENT,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_object_type;

typedef struct s_object
{
	t_point3D		point;
	t_vector3D		vector;
	t_object_type	type;
	float			ratio;
	uint32_t		color;
}					t_object;
#endif
