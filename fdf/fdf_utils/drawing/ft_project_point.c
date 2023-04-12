/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:17:29 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:15:22 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_vector	ft_multiply_vector_by_matrix(t_3d_vector v, t_3d_matrix m)
{
	double	*lv;

	lv = (double [3]){v.x, v.y, v.z};
	v.x = lv[0] * m.i.x + lv[1] * m.i.y + lv[2] * m.i.z;
	v.y = lv[0] * m.j.x + lv[1] * m.j.y + lv[2] * m.j.z;
	v.z = lv[0] * m.k.x + lv[1] * m.k.y + lv[2] * m.k.z;
	return (v);
}

t_3d_matrix	ft_get_rot_matrix(double deg, char axis)
{
	if (axis == 'x')
		return ((t_3d_matrix){
			(t_3d_vector){1, 0, 0, 0},
			(t_3d_vector){0, cos(deg), -sin(deg), 0},
			(t_3d_vector){0, sin(deg), cos(deg), 0}
	});
	if (axis == 'y')
		return ((t_3d_matrix){
			(t_3d_vector){cos(deg), 0, -sin(deg), 0},
			(t_3d_vector){0, 1, 0, 0},
			(t_3d_vector){sin(deg), 0, cos(deg), 0}
	});
	if (axis == 'z')
		return ((t_3d_matrix){
			(t_3d_vector){cos(rad(deg)), -sin(rad(deg)), 0, 0},
			(t_3d_vector){sin(rad(deg)), cos(rad(deg)), 0, 0},
			(t_3d_vector){0, 0, 1, 0}
	});
	return ((t_3d_matrix){
		(t_3d_vector){1, 0, 0, 0},
		(t_3d_vector){0, 1, 0, 0},
		(t_3d_vector){0, 0, 1, 0}
	});
}

t_3d_vector	ft_iso(t_3d_vector vec, t_fdf *fdf)
{
	double		x_deg;
	double		z_deg;

	fdf->depth_change = 1;
	vec.z *= fdf->depth_change;
	z_deg = 45;
	x_deg = atan(sqrt(2));
	vec = ft_multiply_vector_by_matrix(vec, ft_get_rot_matrix(z_deg, 'z'));
	vec = ft_multiply_vector_by_matrix(vec, ft_get_rot_matrix(x_deg, 'x'));
	fdf->z_deg = z_deg;
	fdf->x_deg = x_deg;
	fdf->y_deg = 0;
	return (vec);
}

t_3d_vector	ft_parallel(t_3d_vector vec, t_fdf *fdf)
{
	vec.z *= fdf->depth_change;
	fdf->x_deg = 0;
	fdf->y_deg = 0;
	fdf->z_deg = 0;
	return (vec);
}

t_3d_vector	ft_angular(t_3d_vector vec, t_fdf *fdf)
{
	vec.z *= fdf->depth_change;
	vec = ft_multiply_vector_by_matrix(vec,
			ft_get_rot_matrix(fdf->z_deg, 'z'));
	vec = ft_multiply_vector_by_matrix(vec,
			ft_get_rot_matrix(fdf->x_deg, 'x'));
	vec = ft_multiply_vector_by_matrix(vec,
			ft_get_rot_matrix(fdf->y_deg, 'y'));
	return (vec);
}
