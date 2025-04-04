/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:35:42 by tcali             #+#    #+#             */
/*   Updated: 2025/04/03 18:38:03 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/includes/ft_printf.h"
#include "../includes/so_long.h"

void	print_missing_file(t_data *data)
{
	if (!data->assets.xpm_floor)
		ft_printf("Error loading image: %s\n", data->assets.floor);
	if (!data->assets.xpm_wall)
		ft_printf("Error loading image: %s\n", data->assets.wall);
	if (!data->assets.xpm_collect)
		ft_printf("Error loading image: %s\n", data->assets.collect);
	if (!data->assets.xpm_player)
		ft_printf("Error loading image: %s\n", data->assets.player);
	if (!data->assets.xpm_exit)
		ft_printf("Error loading image: %s\n", data->assets.exit);
}
