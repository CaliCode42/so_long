/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/04/01 11:11:05 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/ft_printf.h"
#include "../includes/so_long.h"

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
	set_textures(data, x, y);
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