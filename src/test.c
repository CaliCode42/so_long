/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/03/28 18:19:50 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"

void	load_assets(t_data *data)
{
	data->assets.height = 80;
	data->assets.width = 80;
	data->assets.floor = "./textures/ground_water.xpm";
	data->assets.wall = "./textures/trees_rock.xpm";
	data->assets.player = "./textures/Undead.xpm";
	//data->assets.collect = "./textures/";
	//data->assets.exit = "./textures/.xpm";
	data->assets.xpm_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.floor, &(data->assets.width), &(data->assets.height));
	data->assets.xpm_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.wall, &(data->assets.width), &(data->assets.height));
	data->assets.xpm_player = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.player, &(data->assets.width), &(data->assets.height));
	//data->img.img_collect = mlx_xpm_file_to_image(data->mlx_ptr,
	//		data->img.collect, &(data->img.width), &(data->img.height));
	//data->img.img_exit = mlx_xpm_file_to_image(data->mlx_ptr, data->img.exit,
	//		&(data->img.width), &(data->img.height));
	if (!data->assets.xpm_floor || !data->assets.xpm_wall
		|| !data->assets.xpm_player)
	{
		printf("Error loading images.\n");
		exit(1);
	}
}

int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->floor, x, y);
	// Register key release hook
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	// Register destroy hook
	mlx_hook(data->win_ptr, DestroyNotify,
		StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
