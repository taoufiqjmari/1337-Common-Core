/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:01:08 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 09:52:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/draw.h"

void	put_pixel_to_img(int x, int y, int color)
{
	if (x >= g_mlx.win_w || y >= g_mlx.win_h)
		return ;
	g_mlx.addr[y * g_mlx.win_w + x] = color;
}

void	rect(int i, int j, int color)
{
	int x;
	int y;

	x = 0;
	while (x < MINIMAP_SCALE_FACTOR * TS)
	{
		y = 0;
		while (y < MINIMAP_SCALE_FACTOR * TS)
		{
			if (x == 0 || x == TS - 1 || y == 0 || y == TS - 1)
				put_pixel_to_img((x + i), (y + j), 0x00000000);
			else
				put_pixel_to_img((x + i), (y + j), color);
			y++;
		}
		x++;
	}
}

void	circle(int i, int j, int color)
{
	int	angle;
	int radius;
	int	x;
	int	y;

	angle = 0;
	radius = 0;
	g_ply.radius = TS / 16;
	while (radius < g_ply.radius)
	{
		angle = 0;
		while (angle < 360)
		{
			x = i + (radius * cos(rad(angle)));
			y = j + (radius * sin(rad(angle)));
			put_pixel_to_img(x, y, color);
			angle++;
		}
		radius++;
	}
}

int		abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void	line(int x, int y, int color)
{
	t_line	line;

	line.dx = x - (int)(MINIMAP_SCALE_FACTOR * g_ply.ply_x);
	line.dy = y - (int)(MINIMAP_SCALE_FACTOR * g_ply.ply_y);
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
	line.x_inc = line.dx / (float)line.steps;
	line.y_inc = line.dy / (float)line.steps;
	line.x = (int)(MINIMAP_SCALE_FACTOR * g_ply.ply_x);
	line.y = (int)(MINIMAP_SCALE_FACTOR * g_ply.ply_y);
	line.i = 0;
	while (line.i <= line.steps)
	{
		put_pixel_to_img(line.x, line.y, color);
		line.x += line.x_inc;
		line.y += line.y_inc;
		line.i++;
	}
}
