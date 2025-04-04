/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:54:57 by tcali             #+#    #+#             */
/*   Updated: 2025/04/04 17:16:00 by tcali            ###   ########.fr       */
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
			have at least one collectibles (C)
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

//fct which calls other fcts to check if map is valid.
int	check_map(t_data *data)
{
	set_content(data);
	if (is_squared(data->map, data) == 0)
		return (0);
	if (enclosed_walls(data->map, data) == 0)
		return (0);
	if (check_symbols(data->map, data) == 0)
		return (0);
	if (check_valid_map(data->map, data) == 0)
		return (ft_printf("Uh oh, map is not valid, trying to fool me?\n"), 0);
	return (ft_printf("Beautiful map, muchas gracias.\n"), 1);
}

//fct to count nb of lines map's file. 
//(to know which size to alloc for the map)
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

//fct which reads the map from fd and fetch it to struct data->map.
//Then checks if map is valid.
int	read_map(int fd, t_data *data, const char *map_path)
{
	int		i;
	char	*line;

	i = 0;
	data->height = count_lines(map_path);
	ft_printf("nb of lines : %d\n\n", data->height);
	if (data->height <= 0)
		return (0);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->map[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	data->map[i] = NULL;
	if (check_map(data) == 0)
		return (clean_exit(data), 0);
	return (1);
}

//fct to parse the map and stock the data 
/*
count nb of lines in file.
OK	if no lines -> file is empty -> return
OK	if file not empty -> use gnl to copy file's content into data->map.

check if content OK : 
OK	squared map 					>> is_squared_map
OK	enclosed by walls 				>> enclosed_walls
OK	only one E/P 					>> check_symbols
OK	at least three C 				>> check_symbols
OK	no other symbols in map (01ECP) >> check_symbols
OK store size of map (height/widht) >> get_map_size? 
			May be stored directly with is_squared map 
			(storing in data after checking if squared.)
*/

//Prototype for fct to check map's validity.
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