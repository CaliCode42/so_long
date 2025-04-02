/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:54:57 by tcali             #+#    #+#             */
/*   Updated: 2025/04/02 17:00:32 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

/*
First need to check type of file (must be .ber)
Then need to check if file is not empty.

If map file has the right format and is not empty>>
	map must be rectangular
				enclosed by walls (first and last lines + columns = 1)
			have only one exit (E)
			have only one start position (P)
			have at least three collectibles (C)
*/

//fct to check if map's format OK, expected ".ber"
//Returns 1 if OK, 0 if KO.
int	is_map_ber(char *str)
{
	char	*ber;

	ber = ".ber";
	if (ft_strnstr(str, ber, ft_strlen(str)) == NULL)
		return (0);
	return (1);
}

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
			ft_printf("Uh oh, map not squared.\n");
			return (0);
		}
		i++;
	}
	ft_printf("map is squared, muchas gracias.\n");
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
			if (h == 0 || h == data->height)
			{
				if (map[h][w] != data->content.w)
					return (printf("Oopsie, there's a hole in the wall.\n"), 0);
			}
			if (w == 0 || w == data->width)
			{
				if (map[h][w] != data->content.w)
					return (printf("Oopsie, there's a hole in the wall.\n"), 0);
			}
			w++;
		}
		h++;
	}
	ft_printf("map is nicely enclosed by walls.\n");
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
	if (data->content.count_c < 3)
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

//fct to free map when map KO or before program end.
void	ft_free_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free (data->map);
}

void	set_content(t_data *data)
{
	data->content.f = '0';
	data->content.w = '1';
	data->content.p = 'P';
	data->content.c = 'C';
	data->content.e = 'E';
	data->content.count_p = 0;
	data->content.count_c = 0;
	data->content.count_e = 0;
}

int	check_map(t_data *data)
{
	set_content(data);
	if (is_squared(data->map, data) == 0)
		return (0);
	if (enclosed_walls(data->map, data) == 0)
		return (0);
	if (check_symbols(data->map, data) == 0)
		return (0);
	return (ft_printf("Beautiful map, muchas gracias.\n"), 1);
}

int	count_lines(const char *map_path)
{
	int		fd;
	int		chars;
	int		line_count;
	char	tmp;

	line_count = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	chars = read(fd, &tmp, 1);
	while (chars > 0)
	{
		if (tmp == '\n')
			line_count++;
		chars = read(fd, &tmp, 1);
	}
	close(fd);
	if (chars == -1)
		return (-1);
	return (line_count);
}

void	read_map(int fd, t_data *data, const char *map_path)
{
	int		i;
	char	*line;

	i = 0;
	data->height = count_lines(map_path);
	ft_printf("nb of lines : %d\n\n", data->height);
	if (data->height <= 0)
		return ;
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf("map's line : \t%s", line);
		data->map[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	data->map[i] = NULL;
	i = 0;
	ft_printf("\n");
	while (data->map[i])
	{
		ft_printf("map : \t\t[%s]\n", data->map[i]);
		i++;
	}
	if (check_map(data) == 0)
		ft_free_map(data);
}

//fct to parse the map and stock the data 
/*
count nb of lines in file.
OK	if no lines -> file is empty -> return
OK	if file not empty -> use gnl to copy file's content into data->map.

check if content OK : 
OK	squared map 					>> is_squared_map
OK	enclosed by walls 				>> enclosed_walls
	only one E/P 					>> check_symbols
	at least three C 				>> check_symbols
	no other symbols in map (01ECP) >> check_symbols
store size of map (height/widht) 	>> get_map_size? 
			May be stored directly with is_squared map 
			(storing in data after checking if squared.)
*/

//Prototype fo fct to check map's validity.
// if (all_collectables_collected && exit_count == 1)
	// return map_valid;
// if (on_wall)
	// return map_invalid;
// if (on_collectable)
	// collectables++;
// if (on_exit)
	// exits++;
// replace_current_position_with_wall;
// if (one_of_the_four_adjacent_directions_is_possible)
	// return map_valid;
// return map_invalid;