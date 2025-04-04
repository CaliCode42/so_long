/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:34:48 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 16:31:30 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

void	init_data(t_data *data)
{
	data->count = 0;
	data->height = 0;
	data->width = 0;
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
}

void	set_content(t_data *data)
{
	data->content.f = '0';
	data->content.w = '1';
	data->content.p = 'P';
	data->content.c = 'C';
	data->content.e = 'E';
	data->content.count_p = 0;
	data->content.count_c = 0;
	data->content.count_e = 0;
}

//fct to load textures
void	load_assets(t_data *data)
{
	data->assets.height = 80;
	data->assets.width = 80;
	data->assets.floor = "./textures/used/floor.xpm";
	data->assets.wall = "./textures/used/Tree.xpm";
	data->assets.player = "./textures/used/undead.xpm";
	data->assets.collect = "./textures/used/Collectibles.xpm";
	data->assets.exit = "./textures/used/exit.xpm";
	data->assets.xpm_floor = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.floor, &(data->assets.width), &(data->assets.height));
	data->assets.xpm_wall = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.wall, &(data->assets.width), &(data->assets.height));
	data->assets.xpm_player = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.player, &(data->assets.width), &(data->assets.height));
	data->assets.xpm_collect = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.collect, &(data->assets.width),
			&(data->assets.height));
	data->assets.xpm_exit = mlx_xpm_file_to_image(data->mlx_ptr,
			data->assets.exit, &(data->assets.width), &(data->assets.height));
	if (!data->assets.xpm_floor || !data->assets.xpm_collect
		|| !data->assets.xpm_wall)
	{
		print_missing_file(data);
		exit(1);
	}
}

//fct to set the different textures.
void	set_textures(t_data *data, int x, int y)
{
	if (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->assets.xpm_floor, x, y) == 0)
		print_missing_file(data);
	if (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->assets.xpm_wall, x, y) == 0)
		print_missing_file(data);
	if (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->assets.xpm_collect, x, y) == 0)
		print_missing_file(data);
	if (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->assets.xpm_player, x, y) == 0)
		print_missing_file(data);
	if (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->assets.xpm_exit, x, y) == 0)
		print_missing_file(data);
}

//fct to free map when map KO or before program end.
void	ft_free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}
