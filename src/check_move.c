/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:12:58 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 15:04:49 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

/*
before moving P, need to check if move is possible : new position must not be 
a wall. >> need a fct to check this 
	if move not possible, don't do anything.
	if move is possible :
		if new position == collectible >> replace C by 0 on map, count_c--
										  when count_c == 0, exit ok.
		if new position == exit && count_c == 0 >> clean_exit.
		else just move P to new tile.
*/

//is_move_possible
//fct which checks if requested move is possible : new position != wall.
//(1 = OK, 0 = KO)
int	is_move_possible(t_data *data, char c)
{
	if (c == data->content.w)
		return (0);
	else if (c == data->content.e && data->content.count_c > 0)
		return (0);
	return (1);
}

//check_new_tile
//fct which checks what's on the next position.
//if collectible >> update count_c and map (return 1)
//if exit && count_c == 0 >> clean_exit return (-1)
//else >> return (0)
int	check_new_tile(t_data *data, char c)
{
	if (c == data->content.c)
	{
		data->content.count_c--;
		return (1);
	}
	else if (c == data->content.e && data->content.count_c == 0)
		return (-1);
	else
		return (0);
}
