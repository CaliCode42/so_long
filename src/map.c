/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:54:57 by tcali             #+#    #+#             */
/*   Updated: 2025/04/01 13:55:15 by tcali            ###   ########.fr       */
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
	ft_printf("big = [%s]\nlittle = [%s]\n", str, ber);
	if (file_ok == NULL)
		return (0);
	return (1);
}

//fct to check if file is empty, returns 1 if empty, 0 if OK.
//int	is_file_empty(int fd);
