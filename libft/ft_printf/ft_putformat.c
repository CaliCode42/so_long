/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcali <tcali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:39:56 by tcali             #+#    #+#             */
/*   Updated: 2025/03/25 23:57:05 by tcali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h> 

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putformat(t_printf *list, char c)
{
	ft_putchar(c);
	list->nb_chars++;
}
