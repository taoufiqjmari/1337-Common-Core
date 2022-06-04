/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:42:18 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/29 12:49:33 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sprite.h"

void	sprite(int i, int j)
{
	if (g_file.map[i][j + 1] == ' ' || g_file.map[i][j - 1] == ' '
		|| g_file.map[i - 1][j] == ' ' || g_file.map[i + 1][j] == ' ')
		my_exit("Sprite is next to space.");
	g_sprite.count++;
}

void	salloc(void)
{
	if (!(g_sprites = malloc(sizeof(t_sprites) * g_sprite.count)))
		my_exit("Sprite allocation failed.");
}

void	put_data(int i, int j)
{
	static int	index = 0;

	i += TS / 2;
	j += TS / 2;
	g_sprites[index].x = j;
	g_sprites[index].y = i;
	index++;
}

void	sprite_data(void)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < g_file.map_height)
	{
		j = 0;
		while (j < g_file.map_width)
		{
			if (g_file.map[i][j] == '2')
				put_data(i * TS, j * TS);
			j++;
		}
		i++;
	}
}

void	get_distance(void)
{
	int		i;

	i = 0;
	while (i < g_sprite.count)
	{
		g_sprites[i].distance = pythagore(g_ply.ply_x, g_ply.ply_y,
											g_sprites[i].x, g_sprites[i].y);
		g_sprites[i].angle = atan2(g_sprites[i].y - g_ply.ply_y,
									g_sprites[i].x - g_ply.ply_x);
		if (g_sprites[i].angle - (g_ply.rotation_ang - FOV_ANG / 2) > rad(180))
			g_sprites[i].angle -= rad(360);
		if (g_sprites[i].angle - (g_ply.rotation_ang - FOV_ANG / 2) < -rad(180))
			g_sprites[i].angle += rad(360);
		i++;
	}
}
