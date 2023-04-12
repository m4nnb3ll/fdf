/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:32:57 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/17 19:28:53 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_color_from_str(char *str)
{
	t_color	color;

	if (str && str + 2)
	{
		color = ft_split_color(ft_atoi_base(str + 2, 16));
		if (ft_strlen(str + 2) > 0 && ft_strlen(str + 2) < 7)
			color.a = 0xFF;
		return (ft_merge_colors(color.r, color.g, color.b, color.a));
	}
	return (ft_merge_colors(0xFF, 0xFF, 0xFF, 0xFF));
}

// Little endian
uint32_t	ft_merge_colors(int r, int g, int b, int a)
{
	if (ENDIANESS == 0)
		return (a << 24 | b << 16 | g << 8 | r);
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	ft_split_color(uint32_t rgba)
{
	t_color	color;

	color = (t_color){0, 0, 0, 0};
	if (rgba > 0xFFFFFF)
		color.a = 8;
	color.r = (rgba >> (16 + color.a)) & 0xFF;
	color.g = (rgba >> (8 + color.a)) & 0xFF;
	color.b = (rgba >> color.a) & 0xFF;
	if (color.a)
		color.a = rgba & 0xFF;
	return (color);
}
