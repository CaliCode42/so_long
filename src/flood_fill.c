/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:08:11 by tcali             #+#    #+#             */
/*   Updated: 2025/04/05 18:16:49 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

//fct which copy map to avoid any modif on original map while flood_filling.
//returns char **copy.
char	**copy_map(char **map, int height)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			ft_free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

//void	print_map(char **map)
//{
//	int	i;

//	i = 0;
//	while (map[i])
//	{
//		ft_printf("map : \t\t[%s]\n", map[i]);
//		i++;
//	}
//}

int	reachable_tile(char **map, int h, int w)
{
	if (map[h][w] == '1' || map[h][w] == 'V')
		return (0);
	if (map[h][w] == 'R')
		return (1);
	if (map[h][w] != 'E')
		map[h][w] = 'V';
	if (reachable_tile(map, h + 1, w) == 1)
		return (1);
	if (reachable_tile(map, h, w + 1))
		return (1);
	if (reachable_tile(map, h - 1, w))
		return (1);
	if (reachable_tile(map, h, w - 1))
		return (1);
	return (0);
}

int	exit_reachable(char **map, int h, int w, t_data *data)
{
	if (map[h + 1][w] == '1' && map[h - 1][w] == '1'
		&& map[h][w + 1] == '1' && map[h][w - 1] == '1')
		return (0);
	if (data->content.copy_count_c == 0 && reachable_tile(map, h, w) == 1)
		return (1);
	return (0);
}

//fct which run through every reachable tile of the map
//and mark them as 'R' (reached).
void	flood_fill(char **map, int h, int w, t_data *data)
{
	if (map[h][w] == '1' || map[h][w] == 'R')
		return ;
	if (map[h][w] == 'E' && data->content.copy_count_c > 0)
	{
		if (exit_reachable(map, h, w, data) == 0)
			return ;
		map[h][w] = 'R';
	}
	if (map[h][w] == 'C')
		data->content.copy_count_c--;
	map[h][w] = 'R';
	flood_fill(map, h + 1, w, data);
	flood_fill(map, h - 1, w, data);
	flood_fill(map, h, w + 1, data);
	flood_fill(map, h, w - 1, data);
}

int	check_valid_map(char **map, t_data *data)
{
	char	**map_copy;
	int		h;
	int		w;

	map_copy = copy_map(map, data->height);
	if (!map_copy)
		return (0);
	data->content.copy_count_c = data->content.count_c;
	flood_fill(map_copy, data->p_pos.h, data->p_pos.w, data);
	h = 0;
	while (h < data->height)
	{
		w = 0;
		while (w < data->width)
		{
			if (map_copy[h][w] == 'C' || map_copy[h][w] == 'E')
			{
				if (map_copy[h][w] == 'E')
				{
					if (exit_reachable(map_copy, h, w, data) == 1)
					{
						map_copy[h][w] = 'R';
						return (1);
					}
				}
				ft_free_map(map_copy);
				return (0);
			}
			w++;
		}
		h++;
	}
	ft_free_map(map_copy);
	return (1);
}
