/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:12:58 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 17:21:56 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

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

//fct which checks what's on the next position.
//if collectible >> update count_c (return 1)
//if exit && count_c == 0 >> return (-1)
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
