/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:42:15 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 17:20:45 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../libft/includes/ft_printf.h"
#include "../includes/so_long.h"

//fct to destroy images before clean_exit.
void	destroy_xpm(t_data *data)
{
	if (data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->assets.xpm_floor);
		mlx_destroy_image(data->mlx_ptr, data->assets.xpm_wall);
		mlx_destroy_image(data->mlx_ptr, data->assets.xpm_player);
		mlx_destroy_image(data->mlx_ptr, data->assets.xpm_collect);
		mlx_destroy_image(data->mlx_ptr, data->assets.xpm_exit);
	}
	clean_exit(data);
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
	if (data)
	{
		if (data->map != NULL)
		{
			ft_free_map(data->map);
			data->map = NULL;
		}
		free(data);
		data = NULL;
	}
	exit(0);
}

//fct to kill the processes of display
int	on_destroy(t_data *data)
{
	clean_exit(data);
	return (0);
}

//fct to call when a key is pressed
//QWERTY
//int	on_keypress(int keysym, t_data *data)
//{
//	ft_printf("Pressed key: %d\\n", keysym);
//	if (keysym == XK_Escape)
//		clean_exit(data);
//	if (keysym == XK_w || keysym == XK_UP)
//		move_up(data);
//	if (keysym == XK_s || keysym == XK_Down)
//		move_down(data);
//	if (keysym == XK_a || keysym == XK_Left)
//		move_left(data);
//	if (keysym == XK_d || keysym == XK_Right)
//		move_right(data);
//	return (0);
//}

//fct to call when a key is pressed
//AZERTY
int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clean_exit(data);
	if (keysym == XK_z || keysym == XK_Up)
		move_up(data);
	if (keysym == XK_s || keysym == XK_Down)
		move_down(data);
	if (keysym == XK_q || keysym == XK_Left)
		move_left(data);
	if (keysym == XK_d || keysym == XK_Right)
		move_right(data);
	if (data->map)
		render_movables(data);
	return (0);
}
