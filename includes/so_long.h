/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:35:44 by tcali             #+#    #+#             */
/*   Updated: 2025/04/02 16:42:54 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../mlx/mlx.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h" 
# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_con
{
	char	f;
	char	w;
	char	p;
	char	c;
	char	e;
	int		count_p;
	int		count_c;
	int		count_e;
}			t_con;

typedef struct s_ass
{
	void	*xpm_floor;
	void	*xpm_wall;
	void	*xpm_player;
	void	*xpm_collect;
	void	*xpm_exit;
	int		height;
	int		width;
	char	*floor;
	char	*wall;
	char	*player;
	char	*collect;
	char	*exit;
}				t_ass;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		width;
	int		height;
	int		count;
	t_con	content;
	t_ass	assets;
}			t_data;

//functions
void	load_assets(t_data *data);

//Textures
void	load_assets(t_data *data);
void	set_textures(t_data *data, int x, int y);

//Map
int		is_map_ber(char *str);
void	read_map(int fd, t_data *data, const char *map_path);

//Kill_process
void	clean_exit(t_data *data);
int		on_destroy(t_data *data);
int		on_keypress(int keysym, t_data *data);

//Debug
void	print_missing_file(t_data *data);

#endif