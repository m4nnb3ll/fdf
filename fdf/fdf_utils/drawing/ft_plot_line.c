/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plot_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 01:12:08 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 14:42:02 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x <= WIDTH - 1 && y <= HEIGHT - 1)
		mlx_put_pixel(img, x, y, color);
}

void	ft_plot_line_low(t_3d_vector p0, t_3d_vector p1, mlx_image_t *img)
{
	t_plot_line_tools	plt;
	t_3d_vector			coor;

	plt.dx = p1.x - p0.x;
	plt.dy = p1.y - p0.y;
	plt.yi = 1;
	if (plt.dy < 0)
	{
		plt.yi = -1;
		plt.dy *= -1;
	}
	plt.d = (2 * plt.dy) - plt.dx;
	coor.x = p0.x;
	coor.y = p0.y;
	while (coor.x <= p1.x)
	{
		ft_put_pixel(img, coor.x, coor.y, ft_grad_pt(p0, p1, coor));
		if (plt.d > 0)
		{
			coor.y += plt.yi;
			plt.d += -2 * plt.dx;
		}
		plt.d += 2 * plt.dy;
		coor.x++;
	}
}

void	ft_plot_line_high(t_3d_vector p0, t_3d_vector p1, mlx_image_t *img)
{
	t_plot_line_tools	plt;
	t_3d_vector			coor;

	plt.dx = p1.x - p0.x;
	plt.dy = p1.y - p0.y;
	plt.xi = 1;
	if (plt.dx < 0)
	{
		plt.xi = -1;
		plt.dx *= -1;
	}
	plt.d = (2 * plt.dx) - plt.dy;
	coor.x = p0.x;
	coor.y = p0.y;
	while (coor.y <= p1.y)
	{
		ft_put_pixel(img, coor.x, coor.y, ft_grad_pt(p0, p1, coor));
		if (plt.d > 0)
		{
			coor.x += plt.xi;
			plt.d += -2 * plt.dy;
		}
		plt.d += 2 * plt.dx;
		coor.y++;
	}
}

void	ft_plot_line(t_3d_vector p0, t_3d_vector p1, mlx_image_t *img)
{
	int	dx;
	int	dy;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	if (abs(dx) > abs(dy))
	{
		if (p1.x - p0.x > 0)
			ft_plot_line_low(p0, p1, img);
		else
			ft_plot_line_low(p1, p0, img);
	}
	else
	{
		if (p1.y - p0.y > 0)
			ft_plot_line_high(p0, p1, img);
		else
			ft_plot_line_high(p1, p0, img);
	}
}
