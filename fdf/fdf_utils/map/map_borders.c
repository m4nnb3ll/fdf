/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:24:28 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:15:07 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// returns a struct containing min and max of x,y
t_map_borders	ft_get_map_borders(t_map_elem	**map, double scale, t_fdf *fdf)
{
	int				i;
	int				j;
	t_map_borders	dims;
	t_3d_vector		point;

	dims.min = (t_2d_vector){0, 0};
	dims.max = (t_2d_vector){0, 0};
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (!map[i][++j].end)
		{
			point = ft_iso(ft_scale(ft_get_vector(map[i][j]), scale), fdf);
			if (floor(point.x) < dims.min.x)
				dims.min.x = floor(point.x);
			else if (ceil(point.x) > dims.max.x)
				dims.max.x = ceil(point.x);
			if (floor(point.y) < dims.min.y)
				dims.min.y = floor(point.y);
			else if (ceil(point.y) > dims.max.y)
				dims.max.y = ceil(point.y);
		}
	}
	return (dims);
}
