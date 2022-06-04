/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:59:19 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 18:03:45 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sprite.h"

void	ft_sort(void)
{
	int			i;
	t_sprites	temp;

	i = 0;
	while (i < g_sprite.count - 1)
	{
		if (g_sprites[i].distance < g_sprites[i + 1].distance)
		{
			temp = g_sprites[i + 1];
			g_sprites[i + 1] = g_sprites[i];
			g_sprites[i] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	put_spixel_to_img(int x, int y)
{
	if (x >= g_mlx.win_w || y >= g_mlx.win_h)
		return ;
	if (y < g_mlx.win_h && y >= 0 && g_sprite.color > 0x000000)
		g_mlx.addr[(y * g_mlx.win_w) + x] = g_sprite.color;
}

void	draw_sprite(int x, float distance, float strip_h)
{
	int		i;
	int		j;
	int		y;

	i = x;
	while (i <= x + strip_h)
	{
		j = (g_mlx.win_h - strip_h) / 2;
		y = 0;
		if (i >= 0 && i < g_mlx.win_w && distance < g_rays[i].distance)
		{
			while (j < (g_mlx.win_h + strip_h) / 2 - 1)
			{
				g_sprite.color = g_sprite.texel[(int)(y / strip_h * g_sprite.h)
					* g_sprite.w + (int)((i - x) / strip_h * g_sprite.w)];
				put_spixel_to_img(i, j);
				j++;
				y++;
			}
		}
		i++;
	}
}

void	render_sprite(void)
{
	int		i;
	float	strip_h;
	int		sprite_x;

	i = 0;
	get_distance();
	ft_sort();
	while (i < g_sprite.count)
	{
		strip_h = (TS / g_sprites[i].distance) * g_dis_proj_plane;
		sprite_x = (g_sprites[i].angle - (g_ply.rotation_ang - FOV_ANG / 2))
						/ (FOV_ANG / g_mlx.win_w) - (strip_h / 2);
		draw_sprite(sprite_x, g_sprites[i].distance, strip_h);
		i++;
	}
}
