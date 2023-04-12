/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:26:59 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/17 19:30:44 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_get_position(t_3d_vector start, t_3d_vector end, t_3d_vector curr)
{
	double	diag_full;
	double	diag_first_part;

	diag_full = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
	diag_first_part = sqrt(pow(curr.x - start.x, 2) + pow(curr.y - start.y, 2));
	if (diag_full)
		return (diag_first_part / diag_full);
	return (1);
}

uint32_t	ft_grad_pt_color(uint32_t a, uint32_t b, double position)
{
	t_color	a_rgba;
	t_color	b_rgba;
	t_color	color;

	a_rgba = ft_split_color(a);
	b_rgba = ft_split_color(b);
	color.r = round(a_rgba.r * (1 - position) + b_rgba.r * position);
	color.g = round(a_rgba.g * (1 - position) + b_rgba.g * position);
	color.b = round(a_rgba.b * (1 - position) + b_rgba.b * position);
	color.a = round(a_rgba.a * (1 - position) + b_rgba.a * position);
	return (ft_merge_colors(color.r, color.g, color.b, color.a));
}

uint32_t	ft_grad_pt(t_3d_vector start, t_3d_vector end, t_3d_vector curr)
{
	double	position;

	position = ft_get_position(start, end, curr);
	return (ft_grad_pt_color(start.color, end.color, position));
}
