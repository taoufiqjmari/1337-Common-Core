/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:51:35 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 09:51:39 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rays.h"

float	pythagore(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

_Bool	rays_map_has_wall_at(float new_x, float new_y)
{
	int	map_index_x;
	int	map_index_y;

	map_index_x = new_x / TS;
	map_index_y = new_y / TS;
	return (g_file.map[map_index_y][map_index_x] == ' ' ||
			g_file.map[map_index_y][map_index_x] == '1');
}

void	cast_ray(float ray_ang, int strip_id)
{
	ray_ang = normalize_ang(ray_ang);
	g_r.is_ray_facing_down = ray_ang > rad(0) && ray_ang < rad(180);
	g_r.is_ray_facing_up = !g_r.is_ray_facing_down;
	g_r.is_ray_facing_right = ray_ang > rad(270) || ray_ang < rad(90);
	g_r.is_ray_facing_left = !g_r.is_ray_facing_right;
	cast_horz_ray(ray_ang);
	cast_vert_ray(ray_ang);
	g_r.horz_hit_distance = g_r.found_horz_wall_hit
		? pythagore(g_ply.ply_x, g_ply.ply_y,
					g_r.horz_wall_hit_x, g_r.horz_wall_hit_y)
		: MAXFLOAT;
	g_r.vert_hit_distance = g_r.found_vert_wall_hit
		? pythagore(g_ply.ply_x, g_ply.ply_y,
					g_r.vert_wall_hit_x, g_r.vert_wall_hit_y)
		: MAXFLOAT;
	affect_ray_values(ray_ang, strip_id);
}

void	update_rays(void)
{
	float	ray_ang;
	int		strip_id;

	ray_ang = g_ply.rotation_ang - (FOV_ANG / 2);
	strip_id = 0;
	while (strip_id < g_mlx.win_w)
	{
		cast_ray(ray_ang, strip_id);
		ray_ang += FOV_ANG / g_mlx.win_w;
		strip_id++;
	}
}

void	render_rays(void)
{
	int	i;

	i = 0;
	while (i < g_mlx.win_w)
	{
		line(MINIMAP_SCALE_FACTOR * g_rays[i].wall_hit_x,
				MINIMAP_SCALE_FACTOR * g_rays[i].wall_hit_y,
				0x000000FF);
		i++;
	}
}
