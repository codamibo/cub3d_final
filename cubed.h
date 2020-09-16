/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/12 13:14:28 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/09 20:25:08 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

# define NO			0
# define EA			1
# define SO			2
# define WE			3
# define S			4
# define R 			5
# define F			6
# define C			7
# define X			0
# define Y			1
# define MOVE_SPEED	0.1
# define ROT_SPEED	0.08
# define BMP_MAX	16384

typedef struct		s_sprite{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_sprite_info{
	double			sprite_x;
	double			sprite_y;
	double			inverse;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				width;
	int				hei;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				tex_x;
	int				y;
	int				d;
	int				tex_y;
	unsigned int	color;
}					t_sprite_info;

typedef struct		s_image{
	void			*img;
	char			*addr;
	int				*int_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;
}					t_image;

typedef struct		s_info{
	int				col_floor;
	int				col_ceiling;
	char			*whole_map;
	int				len1;
	int				len2;
	int				xmax;
	int				ymax;
	float			xstart;
	float			ystart;
	char			start_char;
	int				**array;
	int				**array_copy;
	int				num_sprites;
	int				elem_found[8];
	int				start_char_found;
	int				multiple_start_char;
	int				empty_line;
}					t_info;

typedef struct		s_hooks{
	int				w;
	int				a;
	int				s;
	int				d;
	int				l_arrow;
	int				r_arrow;
	int				esc;
	int				key_change;
}					t_hooks;

typedef struct		s_positions{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	char			side;
	unsigned int	color;
	double			w;
	int				h;
	char			wall_type;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				x;
	t_image			textures[5];
	t_sprite		*sprite;
	int				*sprite_order;
	double			*sprite_distance;
	double			*z_buffer;
	double			step;
}					t_positions;

typedef struct		s_vars {
	void			*mlx;
	void			*win;
	int				type;
	int				file_type;
	int				img_index;
	int				argc;
	int				fd;
	int				reso_x;
	int				reso_y;
	t_info			map;
	t_hooks			hooks;
	t_positions		game;
	t_image			image[2];
	t_sprite_info	sp;
}					t_vars;

typedef int			(*t_handler) (char *buf, int *i, t_vars *vars, int len);

int					res(char *buf, int *i, t_vars *vars, int len);
int					path(char *buf, int *i, t_vars *vars, int len);
int					col(char *buf, int *i, t_vars *vars, int len);
unsigned int		add_shade(double amount, unsigned int color);
unsigned int		create_trgb(unsigned int t, unsigned int r, unsigned int g,
					unsigned int b);
void				my_mlx_pixel_put(t_image *img, int x, int y, int color);
void				parse(char **argv, t_vars *vars, int argc);
int					get_next_line(int fd, char **line);
void				skip_spaces(char *buf, int *i, int len);
void				skip_characters(char *buf, int *i, int len);
void				skip_digits(char *buf, int *i, int len);
void				check_map(t_vars *vars);
int					save_map(char *buf, t_vars *vars);
int					make_map_array(t_info *map, int ***array,
					int count_sprites);
int					is_map_character(char c);
int					is_start_character(char c);
int					all_elem_found(t_info *map);
int					key_pressed(int keycode, t_hooks *hooks);
int					key_released(int keycode, t_hooks *hooks);
int					close_win(t_vars *vars);
void				raycast(t_vars *vars);
int					raycast_loop(t_vars *vars);
void				raycast_setup(t_vars *vars);
int					rotate(t_vars *vars);
void				textures(t_vars *vars, int draw_start, int draw_end,
					int line_height);
int					return_error(char *error);
int					sprites(t_vars *vars, t_sprite_info *sp, t_positions *game);
void				save_sprites(t_vars *vars, t_sprite **sprites,
					int **sprite_order, double **sprite_distance);
void				clean_hooks(t_hooks *hooks);
int					free_arrays(t_vars *vars);
void				file_to_image(t_vars *vars, char *str);
int					file_exists(char *filename, t_vars *vars);
int					identifier_functions(char *buf, int *i, t_vars *vars,
					int len);
void				get_addr(t_vars *vars);
void				clean_map(t_vars *vars);
void				dda(t_vars *vars);
int					move(t_vars *vars);
int					screenshot(t_vars *vars);
void				parse_return(t_vars *vars, char *error, int err);
int					save_col(int r, int g, int b, t_vars *vars);
char				*str_join(char *s1, char *s2);
int					str_chr(const char *s, int c);
void				*cal_loc(size_t count, size_t size);
char				*sub_str(char *s, unsigned int start, size_t len);
int					count_end_spaces(char *buf, int *i, int len);

#endif
