/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 22:35:16 by abelayad          #+#    #+#             */
/*   Updated: 2023/03/19 15:53:51 by abelayad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "get_next_line.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>

// MACROS
# define WIDTH 1024
# define HEIGHT 1024
# ifndef ENDIANESS
#  define ENDIANESS 0 //0: little, 1: big
# endif

// STRUCTURES
//	\_	vectors

typedef struct s_2d_vector
{
	int	x;
	int	y;
}	t_2d_vector;

typedef struct s_3d_vector
{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}	t_3d_vector;

// \_	matrix
typedef struct s_3d_matrix
{
	t_3d_vector	i;
	t_3d_vector	j;
	t_3d_vector	k;
}	t_3d_matrix;

//	\_	map
typedef struct s_map_elem
{
	int				x;
	int				y;
	int				z;
	int				original_depth;
	uint32_t		color;
	int				end;
}	t_map_elem;

typedef struct s_map_borders
{
	t_2d_vector	min;
	t_2d_vector	max;
}	t_map_borders;

//	\_	offset
typedef struct s_offset
{
	int	x;
	int	y;
}	t_offset;

//	\_	line ploting
typedef struct s_plot_line_tools
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;
}	t_plot_line_tools;

// \_	color
typedef struct s_color
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
}	t_color;

// \_	fdf
typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map_elem		**map;
	double			scale;
	t_offset		offset;
	double			x_deg;
	double			y_deg;
	double			z_deg;
	double			depth_change;
}	t_fdf;

// ####### FUNCTIONS #######

// MAP
char			**ft_get_strs(int map_fd);
char			***ft_mapstrs_to_strelems(char **map_strs);
t_map_elem		**ft_fill_map_elems(char ***map_str_elems,
					t_map_elem **map_elems);
t_map_elem		**ft_mapstrs_to_elems(char ***map_str_elems);
t_map_elem		**ft_get_map(char *map_path);
void			ft_free_map2ptrs(t_map_elem **map_elems);
t_map_borders	ft_get_map_borders(t_map_elem	**map,
					double scale, t_fdf *fdf);

// COLOR
int				ft_get_color_from_str(char *str);
uint32_t		ft_merge_colors(int r, int g, int b, int a); // Little endian
t_color			ft_split_color(uint32_t rgba);

// GRADIENT
double			ft_get_position(t_3d_vector start, t_3d_vector end,
					t_3d_vector curr);
uint32_t		ft_grad_pt_color(uint32_t a, uint32_t b, double position);
uint32_t		ft_grad_pt(t_3d_vector start, t_3d_vector end,
					t_3d_vector curr);

// PROJECTION
t_3d_vector		ft_multiply_vector_by_matrix(t_3d_vector v, t_3d_matrix m);
t_3d_vector		ft_iso(t_3d_vector vec, t_fdf *fdf);
t_3d_vector		ft_parallel(t_3d_vector vec, t_fdf *fdf);
t_3d_vector		ft_angular(t_3d_vector vec, t_fdf *fdf);

// DRAWING
void			ft_plot_line_low(t_3d_vector p0, t_3d_vector p1,
					mlx_image_t *img);
void			ft_plot_line_high(t_3d_vector p0, t_3d_vector p1,
					mlx_image_t *img);
void			ft_plot_line(t_3d_vector p0, t_3d_vector p1, mlx_image_t *img);
void			ft_transform_and_draw(t_fdf	*fdf, char mode);
void			ft_clear_img(mlx_image_t *img);
void			ft_draw(t_fdf	*fdf,
					t_3d_vector (*t_f)(t_3d_vector v, t_fdf *fdf));

// SCALE N OFFSET

t_3d_vector		ft_scale(t_3d_vector v, double scale);
t_3d_vector		ft_offset(t_3d_vector v, t_offset offset, t_fdf *fdf,
					t_3d_vector (*t_f)(t_3d_vector v, t_fdf *fdf));
t_3d_vector		ft_scale_n_offset(t_3d_vector v, t_fdf *fdf,
					t_3d_vector (*t_f)(t_3d_vector v, t_fdf *fdf));
double			ft_get_scale(t_map_borders map_borders);
t_offset		ft_get_offset(t_map_borders map_borders);

// ERROR
void			ft_error(void);
int				ft_file_name_error(char	*file_name);

// MISC
t_3d_vector		ft_get_vector(t_map_elem map_el);
double			rad(double deg);

#endif
