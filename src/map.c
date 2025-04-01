/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:54:57 by tcali             #+#    #+#             */
/*   Updated: 2025/04/01 16:52:24 by tcali            ###   ########.fr       */
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
	char	*file_ok;
	char	*ber;

	ber = ".ber";
	file_ok = ft_strnstr(str, ber, ft_strlen(str));
	//ft_printf("big = [%s]\nlittle = [%s]\n", str, ber);
	if (file_ok == NULL)
		return (0);
	return (1);
}

//fct to check if file is empty, returns 1 if empty, 0 if OK.
int	is_file_empty(char *str);

//fct to check if map is squared. (1 = OK, 0 = KO).
//store height and with in struct data before return if OK.
int	is_squared(char **map);

//fct to check if map is enclosed by walls. (1 = OK, 0 = KO).
int enclosed_walls(char **map);

//fct to check symbols in the map.
//free map if KO. (E||P > 1 , C < 3 , unknwon symbols).
void	check_symbols(char **map);

//fct to free map when map KO or before program end.
void	ft_free_map(char **map);

//fct to parse the map and stock the data 
/*
split at each '\n' to read line by line.
check if content OK : 
	squared map 					>> is_squared_map
	enclosed by walls 				>> enclosed_walls
	only one E/P 					>> check_symbols
	at least three C 				>> check_symbols
	no other symbols in map (01ECP) >> check_symbols
store size of map (height/widht) 	>> get_map_size? 
			May be stored directly with is_squared map (storing in data after checking if squared.)
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