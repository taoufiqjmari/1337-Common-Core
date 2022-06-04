/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:38:26 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 18:17:03 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_exit(const char *str)
{
	printf("\033[1;31mError\n");
	printf("%s\n", str);
	exit(0);
}

void	my_exit_clean(const char *str)
{
	printf("\033[1;32m%s\n", str);
	exit(0);
}

int		red_cross(void)
{
	my_exit_clean("Red X Clicked!");
	return (0);
}
