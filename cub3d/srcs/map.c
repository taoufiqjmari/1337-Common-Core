/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 09:57:09 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 11:29:00 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"

void	map(int tile_x, int tile_y, int i, int j)
{
	if (g_file.map[i][j] == '1')
		rect(MINIMAP_SCALE_FACTOR * tile_x,
				MINIMAP_SCALE_FACTOR * tile_y,
				0x00ADADAD);
	else if (g_file.map[i][j] == '2')
		sprite_2d(MINIMAP_SCALE_FACTOR * tile_x,
				MINIMAP_SCALE_FACTOR * tile_y);
	else if (g_file.map[i][j] == 'W' || g_file.map[i][j] == 'E'
				|| g_file.map[i][j] == 'S' || g_file.map[i][j] == 'N')
	{
		rect(MINIMAP_SCALE_FACTOR * tile_x,
			MINIMAP_SCALE_FACTOR * tile_y, 0x00F9F9F9);
	}
	else if (g_file.map[i][j] == ' ')
		return ;
	else
		rect(MINIMAP_SCALE_FACTOR * tile_x,
				MINIMAP_SCALE_FACTOR * tile_y,
				0x00F9F9F9);
}

void	render_map(void)
{
	size_t	i;
	size_t	j;
	int		tile_x;
	int		tile_y;

	i = 0;
	while (i < g_file.map_height)
	{
		j = 0;
		while (j < g_file.map_width)
		{
			tile_x = j * TS;
			tile_y = i * TS;
			map(tile_x, tile_y, i, j);
			j++;
		}
		i++;
	}
}

void	sprite_2d(int tile_x, int tile_y)
{
	rect(tile_x, tile_y, 0x00BF4040);
}
