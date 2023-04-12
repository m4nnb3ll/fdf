/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_n_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:19:03 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:21:00 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw(t_fdf	*fdf, t_3d_vector (*t_f)(t_3d_vector v, t_fdf *fdf))
{
	size_t			i;
	size_t			j;
	t_3d_vector		point1;

	i = 0;
	while (fdf->map[i])
	{
		j = 0;
		while (!fdf->map[i][j].end)
		{
			point1 = ft_scale_n_offset(
					ft_get_vector(fdf->map[i][j]), fdf, t_f);
			if (!fdf->map[i][j + 1].end)
				ft_plot_line(point1,
					ft_scale_n_offset(
						ft_get_vector(fdf->map[i][j + 1]), fdf, t_f), fdf->img);
			if (fdf->map[i + 1])
				ft_plot_line(point1,
					ft_scale_n_offset(
						ft_get_vector(fdf->map[i + 1][j]), fdf, t_f), fdf->img);
			j++;
		}
		i++;
	}
}

/* 
	modes:
	I: Isometric projection
*/
void	ft_transform_and_draw(t_fdf	*fdf, char mode)
{
	void	*t_f;

	if (mode == 'I')
	{
		t_f = ft_iso;
		ft_clear_img(fdf->img);
		ft_draw(fdf, t_f);
	}
	else if (mode == 'P')
	{
		t_f = ft_parallel;
		ft_clear_img(fdf->img);
		ft_draw(fdf, t_f);
	}
	else
	{
		t_f = ft_angular;
		ft_clear_img(fdf->img);
		ft_draw(fdf, t_f);
	}
}

void	ft_clear_img(mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;

	if (img)
	{
		i = -1;
		while (++i < img->width)
		{
			j = -1;
			while (++j < img->height)
				mlx_put_pixel(img, j, i, 0);
		}
	}
}
