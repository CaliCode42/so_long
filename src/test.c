/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/04/03 18:41:17 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

void	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			// Placer le sol en premier pour éviter les trous visuels
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->assets.xpm_floor, x * TILE_SIZE, y * TILE_SIZE);

			// Vérifier quel élément est présent à cette position et l'afficher
			if (data->map[y][x] == '1') // Mur
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'C') // Collectible
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_collect, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'E') // Sortie
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_exit, x * TILE_SIZE, y * TILE_SIZE);
			else if (data->map[y][x] == 'P') // Joueur
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->assets.xpm_player, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
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
		printf("Error allocating memory.\n");
		return ;
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, win_width, win_height, "SL");
	if (!data->win_ptr)
	{
		clean_exit(data);
		return ;
	}
	load_assets(data);
	set_textures(data, win_width, win_height);
	render_map(data);
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
		return (ft_printf("program takes one argument.\n"), 1);
	if (is_map_ber(av[1]) == 0)
		return (ft_printf("program takes an arg of type %s.\n", ".ber"), 1);
	else
	{
		data = malloc(sizeof(t_data));
		fd = open(av[1], O_RDONLY);
		ft_printf("fd = [%d]\nav[1] = %s\n", fd, av[1]);
		if (fd > 0)
			read_map(fd, data, av[1]);
		else
			return (ft_printf("Error\nFailed to open file : %s.\n", av[1]), 1);
		close (fd);
		display_game(data);
		return (0);
	}
}

/*int	main(int ac, char **av)
{
	int		fd;

	fd = 0;
	if (ac != 2)
		return (ft_printf("program takes one argument.\n"), 1);
	if (is_map_ber(av[1]) == 0)
		return (ft_printf("program takes an arg of type %s.\n", ".ber"), 1);
	else
	{
		fd = open(av[1], O_RDONLY);
		ft_printf("fd = [%d]\nav[1] = %s\n", fd, av[1]);
		if (fd < 0)
			return (ft_printf("Error\nFailed to open file : %s.\n", av[1]), 1);
		if (get_next_line(fd) == NULL)
		{
			ft_printf("File is empty.\n");
			close(fd);
			return (1);
		}
		ft_printf("File opened successfully and not empty.\n");
		close (fd);
		return (0);
	}
}*/
