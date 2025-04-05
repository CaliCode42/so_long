/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:54:57 by tcali             #+#    #+#             */
/*   Updated: 2025/04/05 15:17:43 by tcali            ###   ########.fr       */
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
	char	*file;
	char	*filename;

	filename = ft_strrchr(str, '/');
	if (!filename)
		filename = str;
	else
		filename++;
	if (*filename == '.')
		return (0);
	ber = ".ber";
	file = ft_strnstr(filename, ber, ft_strlen(filename));
	if (file == NULL)
		return (0);
	else if (ft_strlen(file) > 4)
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
	{
		ft_printf("Error\nOopsie, there's a hole in the wall.\n");
		return (0);
	}
	if (check_symbols(data->map, data) == 0)
		return (0);
	if (check_valid_map(data->map, data) == 0)
	{
		ft_printf("Error\nUh oh, map is not valid, trying to fool me?\n");
		return (0);
	}
	return (1);
}

//fct to count nb of lines map's file. 
//(to know which size to alloc for the map)
int	count_lines(const char *map_path, t_data *data)
{
	int		fd;
	int		chars;
	int		not_empty;
	char	tmp;

	not_empty = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	chars = read(fd, &tmp, 1);
	while (chars > 0)
	{
		if (tmp == '\n')
		{
			if (not_empty)
				data->height++;
			not_empty = 0;
		}
		else if (ft_present("10ECP", tmp))
			not_empty = 1;
		chars = read(fd, &tmp, 1);
	}
	if (not_empty)
		data->height++;
	close(fd);
	if (chars == -1)
		return (-1);
	return (data->height);
}

char	*check_line(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strchr(str, '\n') != NULL)
		return (ft_substr(str, 0, len - 1));
	else
		return (ft_strdup(str));
}

void	print_map(char **map)
{
	int	i = 0;

	ft_printf("\n------ MAP STATE ------\n");
	while (map[i])
	{
		ft_printf("[%s]\n", map[i]);
		i++;
	}
	ft_printf("-----------------------\n");
}


//fct which reads the map from fd and fetch it to struct data->map.
//Then checks if map is valid.
int	read_map(int fd, t_data *data, const char *map_path)
{
	int		i;
	char	*line;

	i = 0;
	count_lines(map_path, data);
	if (data->height <= 0)
		return (ft_printf("Error\nmap's so small it doesn't exist!\n"), 0);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (0);
	line = get_next_line(fd);
	while (line != NULL && i < data->height)
	{
		data->map[i] = check_line(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	free(line);
	data->map[i] = NULL;
	if (check_map(data) == 0)
		return (print_map(data->map), clean_exit(data), 0);
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