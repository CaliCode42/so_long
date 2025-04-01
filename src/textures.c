/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:39:24 by tcali             #+#    #+#             */
/*   Updated: 2025/04/01 11:12:02 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/ft_printf.h"
#include "../includes/so_long.h"

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

//fct to set the different textures.
void	set_textures(t_data *data, int x, int y)
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
