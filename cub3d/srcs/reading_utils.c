/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:28:56 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 17:20:04 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reading.h"

void	init_elements(void)
{
	g_file.r = 0;
	g_file.no = 0;
	g_file.so = 0;
	g_file.we = 0;
	g_file.ea = 0;
	g_file.s = 0;
	g_file.f = 0;
	g_file.c = 0;
	g_file.read = 0;
	g_file.start_map = 0;
	g_file.temp_map = ft_strdup("");
	g_file.map_width = 0;
	g_file.map_height = 0;
	g_ply.player_defined = 0;
	g_sprite.count = 0;
}

void	all_read(void)
{
	if (g_file.r && g_file.no && g_file.so
		&& g_file.we && g_file.ea && g_file.s
		&& g_file.f && g_file.c)
		g_file.read = 1;
}

int		how_many_part(char **part)
{
	int		i;

	i = 0;
	while (part[i])
		i++;
	return (i);
}

void	free_dpointer(char **str)
{
	int		i;

	if (str)
	{
		i = how_many_part(str);
		while (i >= 0)
		{
			free(str[i]);
			str[i] = NULL;
			i--;
		}
		free(str);
	}
	str = NULL;
}

void	is_info_correct(char *part, char c)
{
	int		commas;

	commas = 0;
	if (c == 'r')
	{
		while (*part)
		{
			if (*part >= '0' && *part <= '9')
				part++;
			else if (*part == '\0')
				return ;
			else
				my_exit("Problem with integer input.");
		}
	}
	if (c == 'c')
	{
		while (*part)
		{
			if (*part++ == ',')
				commas++;
		}
		if (commas != 2)
			my_exit("Problem with RGB input.");
	}
}
