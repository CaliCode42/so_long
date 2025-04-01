/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:42:15 by tcali             #+#    #+#             */
/*   Updated: 2025/04/01 11:13:16 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/ft_printf.h"
#include "../includes/so_long.h"

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
	ft_printf("Pressed key: %d\\n", keysym);
	if (keysym == XK_Escape)
		clean_exit(data);
	return (0);
}
