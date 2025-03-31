/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/03/31 15:49:24 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"

void	print_missing_file(t_data *data)
{
	if (!data->assets.xpm_floor)
		printf("Error loading image: %s\n", data->assets.floor);
	if (!data->assets.xpm_wall)
		printf("Error loading image: %s\n", data->assets.wall);
	if (!data->assets.xpm_player)
		printf("Error loading image: %s\n", data->assets.player);
}

//fct to load textures
void	load_assets(t_data *data)
{
	data->assets.height = 80;
	data->assets.width = 80;
	data->assets.floor = "./textures/used/floor.xpm";
	data->assets.wall = "./textures/used/tree.xpm";
	data->assets.player = "./textures/used/undead.xpm";
	//data->assets.collect = "./textures/";
	//data->assets.exit = "./textures/.xpm";
	data->assets.xpm_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.floor, &(data->assets.width), &(data->assets.height));
	// data->assets.xpm_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			// data->assets.wall, &(data->assets.width), &(data->assets.height));
	// data->assets.xpm_player = mlx_xpm_file_to_image(data->mlx_ptr,
			// data->assets.player, &(data->assets.width), &(data->assets.height));
	//data->img.img_collect = mlx_xpm_file_to_image(data->mlx_ptr,
	//		data->img.collect, &(data->img.width), &(data->img.height));
	//data->img.img_exit = mlx_xpm_file_to_image(data->mlx_ptr, data->img.exit,
	//		&(data->img.width), &(data->img.height));
	// if (!data->assets.xpm_floor || !data->assets.xpm_wall
		// || !data->assets.xpm_player)
	// {
		// print_missing_file(data);
		// exit(1);
	// }
	if (!data->assets.xpm_floor)
	{
		print_missing_file(data);
		exit(1);
	}
}

//fct to quit program and free mlx_ptr.
void	clean_exit(t_data *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free(data);
	exit(0);
}

//fct to kill the processes of display
int	on_destroy(t_data *data)
{
	clean_exit(data);
	return (0);
}

//fct to call when Escape is pressed (to kill processes)
int	on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	if (keysym == XK_Escape)
		clean_exit(data);
	return (0);
}

void	display_textures(t_data *data, int x, int y)
{
	int	a;
	int	b;
	int	c;

	a = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->assets.xpm_floor, x, y);
	b = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->assets.xpm_floor, x, y);
	c = mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->assets.xpm_floor, x, y);
	if (!a || !b || !c)
	{
		print_missing_file(data);
	}
}

int	main(void)
{
	t_data	*data;
	int		x;
	int		y;

	x = 0;
	y = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (printf("Error allocating memory.\n"), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, 800, 600, "So Long Game");
	if (!data->win_ptr)
		return (free(data->mlx_ptr), 1);
	load_assets(data);
	display_textures(data, x, y);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		// data->assets.xpm_floor, x, y);
	// Register key release hook
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	// Register destroy hook
	mlx_hook(data->win_ptr, DestroyNotify,
		StructureNotifyMask, &on_destroy, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}


// if (all_collectables_collected && exit_count == 1)
	// return map_valid;
// if (on_wall)
	// return map_invalid;
// if (on_collectable)
	// collectables++;
// if (on_exit)
	// exits++;
// replace_current_position_with_wall;
// if (one_of_the_four_adjacent_directions_is_possible)
	// return map_valid;
// return map_invalid;