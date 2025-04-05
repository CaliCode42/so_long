/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/04/05 14:39:33 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

//fct which renders the fixed elements of the map (background)
//What if map's file contain empty lines? Does it crash?
void	render_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->map[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_floor, x * TILE_SIZE, y * TILE_SIZE);
			if (data->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_wall, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

//fct which renders the movables elements of the map 
//(player, collectibles and exit).
void	render_movables(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (data->map[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_collect, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_exit, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_player, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

int	render_map(t_data *data)
{
	if (!data->map)
		return (-1);
	render_background(data);
	render_movables(data);
	return (0);
}

void	display_game(t_data *data)
{
	int		win_width;
	int		win_height;

	win_width = data->width * TILE_SIZE;
	win_height = data->height * TILE_SIZE;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		printf("Error\nAllocating memory.\n");
		return ;
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, win_width, win_height,
			"Evil Undead loves cats");
	if (!data->win_ptr)
	{
		clean_exit(data);
		return ;
	}
	load_assets(data);
	set_textures(data, win_width, win_height);
	mlx_loop_hook(data->mlx_ptr, render_map, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify,
		StructureNotifyMask, &on_destroy, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	*data;

	fd = 0;
	if (ac != 2)
		return (ft_printf("Error\nProgram takes one argument.\n"), 1);
	if (is_map_ber(av[1]) == 0)
		return (ft_printf("Error\nArg must be of type %s.\n", ".ber"), 1);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		init_data(data);
		fd = open(av[1], O_RDONLY);
		if (fd <= 0)
		{
			free(data);
			return (ft_printf("Error\nFailed to open file : %s.\n", av[1]), 1);
		}
		if (read_map(fd, data, av[1]) == 1)
			display_game(data);
		close (fd);
		return (0);
	}
}
