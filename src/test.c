/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:16:26 by tcali             #+#    #+#             */
/*   Updated: 2025/04/01 17:48:04 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

// int	main(void)
// {
	// t_data	*data;
	// int		x;
	// int		y;

	// x = 0;
	// y = 0;
	// data = malloc(sizeof(t_data));
	// if (!data)
		// return (1);
	// data->mlx_ptr = mlx_init();
	// if (!data->mlx_ptr)
		// return (printf("Error allocating memory.\n"), 1);
	// data->win_ptr = mlx_new_window(data->mlx_ptr, 800, 600, "So Long Game");
	// if (!data->win_ptr)
		// return (free(data->mlx_ptr), 1);
	// load_assets(data);
	// set_textures(data, x, y);
	// // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		// // data->assets.xpm_floor, x, y);
	// // Register key release hook
	// mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	// // Register destroy hook
	// mlx_hook(data->win_ptr, DestroyNotify,
		// StructureNotifyMask, &on_destroy, data);
	// mlx_loop(data->mlx_ptr);
	// return (0);
// }

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
			read_map(fd, data);
		else
			return (ft_printf("Error\nFailed to open file : %s.\n", av[1]), 1);
		close (fd);
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
