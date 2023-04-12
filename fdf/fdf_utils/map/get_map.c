/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:48:19 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 14:41:44 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_get_strs(int map_fd)
{
	char	*gnl_ret;
	char	*str;
	char	*tofree;
	char	**map_strs;

	gnl_ret = get_next_line(map_fd);
	if (!gnl_ret)
		return (NULL);
	str = ft_strdup("");
	if (!str)
		return (NULL);
	while (gnl_ret)
	{
		tofree = str;
		str = ft_strjoin(str, gnl_ret);
		if (!str)
			return (free(gnl_ret), free(tofree), NULL);
		free(tofree);
		gnl_ret = (free(gnl_ret), get_next_line(map_fd));
	}
	map_strs = ft_split(str, '\n');
	if (!map_strs)
		return (free(str), NULL);
	return (free(str), map_strs);
}

char	***ft_mapstrs_to_strelems(char **map_strs)
{
	size_t	i;
	char	***map_str_elems;

	if (!map_strs)
		return (NULL);
	map_str_elems = (char ***)ft_calloc(
			(ft_strs_len(map_strs) + 1), sizeof(char **));
	if (!map_str_elems)
		return (ft_free_char2(map_strs), NULL);
	i = 0;
	while (map_strs[i])
	{
		map_str_elems[i] = ft_split(map_strs[i], ' ');
		if (!map_str_elems[i])
			return (ft_free_char3(map_str_elems),
				ft_free_char2(map_strs), NULL);
		i++;
	}
	return (ft_free_char2(map_strs), map_str_elems);
}

t_map_elem	**ft_fill_map_elems(char ***map_str_elems, t_map_elem **map_elems)
{
	size_t		i;
	size_t		j;
	char		**el_split;

	if (!map_elems)
		return (ft_free_char3(map_str_elems), NULL);
	i = 0;
	while (map_str_elems[i])
	{
		j = 0;
		while (map_str_elems[i][j])
		{
			el_split = ft_split(map_str_elems[i][j], ',');
			if (!el_split)
				return (ft_free_char3(map_str_elems),
					ft_free_map2ptrs(map_elems), NULL);
			map_elems[i][j] = (t_map_elem){j, i, ft_atoi(el_split[0]),
				ft_atoi(el_split[0]), ft_get_color_from_str(el_split[1]), 0};
			ft_free_char2(el_split);
			j++;
		}
		map_elems[i][j] = (t_map_elem){0, 0, 0, 0, 0, 1};
		i++;
	}
	return (ft_free_char3(map_str_elems), map_elems);
}

/*

**t_map
	v
*t_map->|t_map t_map t_map
*t_map->|t_map t_map t_map
*t_map->|t_map t_map t_map

*/

t_map_elem	**ft_mapstrs_to_elems(char ***map_str_elems)
{
	size_t		i;
	t_map_elem	**map_elems;

	if (!map_str_elems)
		return (NULL);
	map_elems = (t_map_elem **)ft_calloc(
			ft_strs_arr_len(map_str_elems) + 1, sizeof(t_map_elem *));
	if (!map_elems)
		return (ft_free_char3(map_str_elems), NULL);
	i = 0;
	while (map_str_elems[i])
	{
		map_elems[i] = (t_map_elem *)ft_calloc(
				ft_strs_len(map_str_elems[i]) + 1, sizeof(t_map_elem));
		if (!map_elems[i])
			return (ft_free_char3(map_str_elems)
				, ft_free_map2ptrs(map_elems), NULL);
		i++;
	}
	return (ft_fill_map_elems(map_str_elems, map_elems));
}

t_map_elem	**ft_get_map(char *map_path)
{
	int		map_fd;

	map_fd = open(map_path, O_RDONLY, 0400);
	if (map_fd < 0)
		return (NULL);
	return (ft_mapstrs_to_elems(ft_mapstrs_to_strelems(ft_get_strs(map_fd))));
}
