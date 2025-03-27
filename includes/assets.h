/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:08:05 by tcali             #+#    #+#             */
/*   Updated: 2025/03/27 15:13:07 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

// Path to assets
# ifndef FLOOR_IMG_PATH
#  define FLOOR_IMG_PATH "../textures/used/ground_water.xpm"
# endif
# ifndef WALL_IMG_PATH
#  define WALL_IMG_PATH "../textures/used/trees_rocks_1.xpm"
# endif
# ifndef PLAYER_IMG_PATH
#  define PLAYER_IMG_PATH "../textures/used/undead.xpm"
# endif

// Assets' related constants
# define NUM_TILES 3

#endif
