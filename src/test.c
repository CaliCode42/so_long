/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/03/27 15:00:11 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "so_long.h"
#include "assets.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>

void	load_assets(t_data *data)
{
	int	width;
	int	height;

	data->floor = mlx_xpm_file_to_image(data->mlx_ptr,
			FLOOR_IMG_PATH, &width, &height);
    data->wall = mlx_xpm_file_to_image(data->mlx_ptr,
			WALL_IMG_PATH, &width, &height);
    data->player = mlx_xpm_file_to_image(data->mlx_ptr,
			PLAYER_IMG_PATH, &width, &height);
	if (!data->floor || !data->wall || !data->player)
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

int main(void)
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
