/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:47:22 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/20 18:51:35 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "cub3d.h"

typedef	struct	s_ply
{
	_Bool		player_defined;
	char		ply_init_dir;
	float		ply_x;
	float		ply_y;
	int			radius;
	int			turn_direction;
	int			walk_direction;
	float		rotation_ang;
	int			straight;
	float		move_speed;
	float		rotation_speed;
}				t_ply;
t_ply			g_ply;

void			define_ply(int tile_x, int tile_y);
int				key_pressed(int keycode, t_ply *g_ply);
void			update_player(void);
_Bool			map_has_wall_at(float new_ply_x, float new_ply_y);
void			render_player(void);

#endif
