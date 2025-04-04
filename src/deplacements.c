/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deplacements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:50:28 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 17:25:37 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

//checks if player can go up. If yes, update map and player position.
void	move_up(t_data *data)
{
	int	new_pos_h;
	int	new_pos_w;

	new_pos_h = data->p_pos.h - 1;
	new_pos_w = data->p_pos.w;
	if (is_move_possible(data, data->map[new_pos_h][new_pos_w]) == 1)
	{
		data->count++;
		ft_printf("Moves : %d\n", data->count);
		if (check_new_tile(data, data->map[new_pos_h][new_pos_w]) == -1)
		{
			ft_printf("Congrats cutiepie, you won in %d moves.\n", data->count);
			destroy_xpm(data);
		}
		data->map[new_pos_h][new_pos_w] = data->content.p;
		data->map[data->p_pos.h][data->p_pos.w] = data->content.f;
		data->p_pos.h = new_pos_h;
	}
}

//checks if player can go down. If yes, update map and player position.
void	move_down(t_data *data)
{
	int	new_pos_h;
	int	new_pos_w;

	new_pos_h = data->p_pos.h + 1;
	new_pos_w = data->p_pos.w;
	if (is_move_possible(data, data->map[new_pos_h][new_pos_w]) == 1)
	{
		data->count++;
		ft_printf("Moves : %d\n", data->count);
		if (check_new_tile(data, data->map[new_pos_h][new_pos_w]) == -1)
		{
			ft_printf("Congrats cutiepie, you won in %d moves.\n", data->count);
			destroy_xpm(data);
		}
		data->map[new_pos_h][new_pos_w] = data->content.p;
		data->map[data->p_pos.h][data->p_pos.w] = data->content.f;
		data->p_pos.h = new_pos_h;
	}
}

//checks if player can go left. If yes, update map and player position.
void	move_left(t_data *data)
{
	int	new_pos_h;
	int	new_pos_w;

	new_pos_h = data->p_pos.h;
	new_pos_w = data->p_pos.w - 1;
	if (is_move_possible(data, data->map[new_pos_h][new_pos_w]) == 1)
	{
		data->count++;
		ft_printf("Moves : %d\n", data->count);
		if (check_new_tile(data, data->map[new_pos_h][new_pos_w]) == -1)
		{
			ft_printf("Congrats cutiepie, you won in %d moves!\n", data->count);
			destroy_xpm(data);
		}
		data->map[new_pos_h][new_pos_w] = data->content.p;
		data->map[data->p_pos.h][data->p_pos.w] = data->content.f;
		data->p_pos.w = new_pos_w;
	}
}

//checks if player can go right. If yes, update map and player position.
void	move_right(t_data *data)
{
	int	new_pos_h;
	int	new_pos_w;

	new_pos_h = data->p_pos.h;
	new_pos_w = data->p_pos.w + 1;
	if (is_move_possible(data, data->map[new_pos_h][new_pos_w]) == 1)
	{
		data->count++;
		ft_printf("Moves : %d\n", data->count);
		if (check_new_tile(data, data->map[new_pos_h][new_pos_w]) == -1)
		{
			ft_printf("Congrats cutiepie, you won in %d moves.\n", data->count);
			destroy_xpm(data);
		}
		data->map[new_pos_h][new_pos_w] = data->content.p;
		data->map[data->p_pos.h][data->p_pos.w] = data->content.f;
		data->p_pos.w = new_pos_w;
	}
}
