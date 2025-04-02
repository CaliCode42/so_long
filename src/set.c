/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:49:52 by tcali             #+#    #+#             */
/*   Updated: 2025/04/02 18:50:15 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/so_long.h"

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
