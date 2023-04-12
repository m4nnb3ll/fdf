/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:25:37 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:21:05 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_get_scale(t_map_borders map_borders)
{
	int	width;
	int	height;

	width = abs(map_borders.max.x - map_borders.min.x);
	height = abs(map_borders.max.y - map_borders.min.y);
	return (ft_min((WIDTH - WIDTH / 8.0) / width
			, (HEIGHT - HEIGHT / 8.0) / height));
}

t_offset	ft_get_offset(t_map_borders map_borders)
{
	int	width;
	int	height;
	int	offset_x;
	int	offset_y;

	width = abs(map_borders.max.x - map_borders.min.x);
	height = abs(map_borders.max.y - map_borders.min.y);
	offset_x = round((WIDTH - width) / 2.0);
	offset_y = round((HEIGHT - height) / 2.0);
	if (map_borders.min.x < 0)
		offset_x += abs((int)round(map_borders.min.x));
	if (map_borders.min.y < 0)
		offset_y += abs((int)round(map_borders.min.y));
	return ((t_offset){offset_x, offset_y});
}

t_3d_vector	ft_get_vector(t_map_elem map_el)
{
	return ((t_3d_vector){map_el.x, map_el.y, map_el.z, map_el.color});
}

double	rad(double deg)
{
	return (deg * M_PI / 180);
}
