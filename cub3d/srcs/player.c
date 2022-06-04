/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:34:39 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 18:24:02 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/player.h"

void	define_ply(int i, int j)
{
	if (!g_ply.player_defined)
	{
		g_ply.player_defined = 1;
		g_ply.ply_x = (j * TS) + TS / 2;
		g_ply.ply_y = (i * TS) + TS / 2;
		if (g_ply.ply_init_dir == 'W')
			g_ply.rotation_ang = rad(180);
		else if (g_ply.ply_init_dir == 'E')
			g_ply.rotation_ang = rad(0);
		else if (g_ply.ply_init_dir == 'S')
			g_ply.rotation_ang = rad(90);
		else if (g_ply.ply_init_dir == 'N')
			g_ply.rotation_ang = rad(270);
	}
	else
		my_exit("Multiple players in map");
}

int		key_pressed(int keycode, t_ply *g_ply)
{
	g_ply->straight = 1;
	if (keycode == CLICK_LEFT)
	{
		g_ply->walk_direction = -1;
		g_ply->straight = 0;
	}
	else if (keycode == CLICK_RIGHT)
	{
		g_ply->walk_direction = +1;
		g_ply->straight = 0;
	}
	else if (keycode == CLICK_DOWN)
		g_ply->walk_direction = -1;
	else if (keycode == CLICK_UP)
		g_ply->walk_direction = +1;
	else if (keycode == CLICK_LEFT_VIEW)
		g_ply->turn_direction = -1;
	else if (keycode == CLICK_RIGHT_VIEW)
		g_ply->turn_direction = +1;
	else if (keycode == CLICK_ESC)
		my_exit_clean("ESP Clicked.");
	render();
	return (0);
}

_Bool	map_has_wall_at(float new_x, float new_y)
{
	int	cur_ply_x;
	int	cur_ply_y;
	int	new_ply_x;
	int	new_ply_y;

	cur_ply_x = g_ply.ply_x / TS;
	cur_ply_y = g_ply.ply_y / TS;
	new_ply_x = new_x / TS;
	new_ply_y = new_y / TS;
	if (g_file.map[new_ply_y][new_ply_x] == ' ' ||
			g_file.map[new_ply_y][new_ply_x] == '1' ||
			g_file.map[new_ply_y][new_ply_x] == '2')
		return (1);
	if (cur_ply_x != new_ply_x && cur_ply_y != new_ply_y)
	{
		if (g_file.map[new_ply_y][cur_ply_x] == '1' ||
				g_file.map[new_ply_y][cur_ply_x] == '2')
			if (g_file.map[cur_ply_y][new_ply_x] == '1' ||
					g_file.map[cur_ply_y][new_ply_x] == '2')
				return (1);
	}
	return (0);
}

void	update_player(void)
{
	float	move_step;
	float	new_x;
	float	new_y;

	g_ply.rotation_ang += g_ply.turn_direction * g_ply.rotation_speed;
	g_ply.rotation_ang = normalize_ang(g_ply.rotation_ang);
	move_step = g_ply.walk_direction * g_ply.move_speed;
	if (g_ply.straight)
	{
		new_x = g_ply.ply_x + cos(g_ply.rotation_ang) * move_step;
		new_y = g_ply.ply_y + sin(g_ply.rotation_ang) * move_step;
	}
	else
	{
		new_x = g_ply.ply_x + cos(g_ply.rotation_ang + rad(90)) * move_step;
		new_y = g_ply.ply_y + sin(g_ply.rotation_ang + rad(90)) * move_step;
	}
	if (!map_has_wall_at(new_x, new_y))
	{
		g_ply.ply_x = new_x;
		g_ply.ply_y = new_y;
	}
	g_ply.turn_direction = 0;
	g_ply.walk_direction = 0;
}

void	render_player(void)
{
	circle(MINIMAP_SCALE_FACTOR * g_ply.ply_x,
			MINIMAP_SCALE_FACTOR * g_ply.ply_y,
			0x00000000);
	line(MINIMAP_SCALE_FACTOR * g_ply.ply_x + cos(g_ply.rotation_ang)
			* MINIMAP_SCALE_FACTOR * TS / 2,
			MINIMAP_SCALE_FACTOR * g_ply.ply_y + sin(g_ply.rotation_ang)
			* MINIMAP_SCALE_FACTOR * TS / 2,
			0x00000000);
}
