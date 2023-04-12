/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:38:17 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/17 19:35:25 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_map2ptrs(t_map_elem **map_elems)
{
	size_t	i;

	i = 0;
	while (map_elems[i])
		free(map_elems[i++]);
	free(map_elems);
}
