/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:20:03 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:37:59 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_hook_rotate_n_translate(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->y_deg += .01;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->y_deg -= .01;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->x_deg += .01;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->x_deg -= .01;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->offset.y -= fdf->scale;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->offset.x += fdf->scale;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->offset.y += fdf->scale;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->offset.x -= fdf->scale;
}

void	ft_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	ft_hook_rotate_n_translate(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_P))
		ft_transform_and_draw(fdf, 'P');
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
		ft_transform_and_draw(fdf, 'I');
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
	{
		if (fdf->scale < 1000)
			fdf->scale += 1;
	}
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT))
	{
		if (fdf->scale > 2)
			fdf->scale -= 1;
	}
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		fdf->depth_change -= .1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		fdf->depth_change += .1;
	ft_transform_and_draw(fdf, 'F');
}

int32_t	ft_boot_err(int argc, char **argv, t_fdf *fdf)
{
	if (argc != 2)
		return (ft_putstr_fd("Usage: ./fdf <map_path>\n", 2), 1);
	if (ft_file_name_error(argv[1]))
		return (ft_putstr_fd("Invalid filename.\n", 2), 1);
	fdf->map = ft_get_map(argv[1]);
	if (!fdf->map)
		return (1);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "🥐 Fil de Fer 🥖", false);
	if (!fdf->mlx)
		ft_error();
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		ft_error();
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) < 0)
		ft_error();
	return (0);
}

int32_t	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (ft_boot_err(argc, argv, &fdf))
		return (1);
	fdf.scale = ft_get_scale(ft_get_map_borders(fdf.map, 1, &fdf));
	fdf.offset = ft_get_offset(ft_get_map_borders(fdf.map, fdf.scale, &fdf));
	ft_transform_and_draw(&fdf, 'I');
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	ft_free_map2ptrs(fdf.map);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
