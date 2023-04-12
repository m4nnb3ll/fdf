/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_n_offset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:18:17 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:20:56 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_vector	ft_scale(t_3d_vector v, double scale)
{
	return ((t_3d_vector){
		v.x * scale,
		v.y * scale,
		v.z * scale,
		v.color
	});
}

t_3d_vector	ft_offset(t_3d_vector v, t_offset offset, t_fdf *fdf
	, t_3d_vector (*t_f)(t_3d_vector v, t_fdf *fdf))
{
	t_3d_vector	nv;

	nv = t_f(v, fdf);
	return ((t_3d_vector){
		nv.x + offset.x,
		nv.y + offset.y,
		nv.z,
		nv.color
	});
}

t_3d_vector	ft_scale_n_offset(t_3d_vector v, t_fdf *fdf
	, t_3d_vector (*t_f)(t_3d_vector v, t_fdf *fdf))
{
	return (ft_offset(ft_scale(v, fdf->scale), fdf->offset, fdf, t_f));
}
