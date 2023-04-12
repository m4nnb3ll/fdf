/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:52:20 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:13:58 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

int	ft_file_name_error(char	*file_name)
{
	size_t	file_name_len;

	file_name_len = ft_strlen(file_name);
	if (file_name_len < 4)
		return (1);
	if (ft_strncmp(&file_name[file_name_len - 4], ".fdf", 4))
		return (1);
	return (0);
}
