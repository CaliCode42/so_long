/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:13:38 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 17:42:02 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

//fct to check if map is squared. (1 = OK, 0 = KO).
//store height and with in struct data before return if OK.
int	is_squared(char **map, t_data *data)
{
	int	i;

	i = 0;
	data->width = ft_strlen(map[i]);
	while (i < data->height)
	{
		if ((int)ft_strlen(map[i]) != data->width)
		{
			ft_printf("Error.\nUh oh, map not squared.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

//fct to check if map is enclosed by walls. (1 = OK, 0 = KO).
int	enclosed_walls(char **map, t_data *data)
{
	int	w;
	int	h;

	h = 0;
	while (h < data->height)
	{
		w = 0;
		while (w < data->width)
		{
			if (h == 0 || h == data->height - 1)
			{
				if (map[h][w] != data->content.w)
					return (0);
			}
			if (w == 0 || w == data->width - 1)
			{
				if (map[h][w] != data->content.w)
					return (printf("Oopsie, there's a hole in the wall.\n"), 0);
			}
			w++;
		}
		h++;
	}
	return (1);
}

int	symb_is_good(char c, t_data *data)
{
	if (c != data->content.f && (c != data->content.w)
		&& (c != data->content.p) && (c != data->content.c)
		&& (c != data->content.e))
		return (ft_printf("Uh oh unknow symbol in the map.\n"), 0);
	if (c == data->content.p)
		data->content.count_p++;
	if (c == data->content.c)
		data->content.count_c++;
	if (c == data->content.e)
		data->content.count_e++;
	return (1);
}

int	count_is_good(t_data *data)
{
	if (data->content.count_c < 1)
		return (ft_printf("Not enough collectibles, don't be greedy.\n"), 0);
	if (data->content.count_e != 1)
		return (ft_printf("Invalid nb of exit, basic maths LOL.\n"), 0);
	if (data->content.count_p != 1)
		return (ft_printf("Invalid nb of player, basic maths LOL.\n"), 0);
	return (1);
}

//fct to check symbols in the map.
//free map if KO. (E||P > 1 , C < 3 , unknwon symbols). (1 = OK, 0 = KO).
int	check_symbols(char **map, t_data *data)
{
	int	h;
	int	w;

	h = 0;
	while (h < data->height)
	{
		w = 0;
		while (w < data->width)
		{
			if (map[h][w] == data->content.p)
			{
				data->p_pos.h = h;
				data->p_pos.w = w;
			}
			if (symb_is_good(map[h][w], data) == 0)
				return (0);
			w++;
		}
		h++;
	}
	if (count_is_good(data) == 0)
		return (0);
	return (1);
}
