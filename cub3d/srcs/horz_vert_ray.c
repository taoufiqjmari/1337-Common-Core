/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horz_vert_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:25:21 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 09:35:15 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rays.h"

void	cast_horz_ray(float ray_ang)
{
	g_r.found_horz_wall_hit = FALSE;
	g_r.horz_wall_hit_x = 0;
	g_r.horz_wall_hit_y = 0;
	g_r.horz_wall_content = 0;
	g_r.yintercept = floor(g_ply.ply_y / TS) * TS;
	g_r.yintercept += g_r.is_ray_facing_down ? TS : 0;
	g_r.xintercept = g_ply.ply_x + (g_r.yintercept - g_ply.ply_y)
					/ tan(ray_ang);
	g_r.ystep = TS;
	g_r.ystep *= g_r.is_ray_facing_up ? -1 : 1;
	g_r.xstep = TS / tan(ray_ang);
	g_r.xstep *= (g_r.is_ray_facing_left && g_r.xstep > 0) ? -1 : 1;
	g_r.xstep *= (g_r.is_ray_facing_right && g_r.xstep < 0) ? -1 : 1;
	g_r.next_horz_touch_x = g_r.xintercept;
	g_r.next_horz_touch_y = g_r.yintercept;
	find_horz_ray_limit();
}

void	find_horz_ray_limit(void)
{
	while (g_r.next_horz_touch_x >= 0
		&& g_r.next_horz_touch_x <= g_file.map_width * TS
		&& g_r.next_horz_touch_y >= 0
		&& g_r.next_horz_touch_y <= g_file.map_height * TS)
	{
		g_r.check_x = g_r.next_horz_touch_x;
		g_r.check_y = g_r.next_horz_touch_y;
		if (g_r.is_ray_facing_up)
			g_r.check_y -= 1;
		if (rays_map_has_wall_at(g_r.check_x, g_r.check_y))
		{
			g_r.horz_wall_hit_x = g_r.next_horz_touch_x;
			g_r.horz_wall_hit_y = g_r.next_horz_touch_y;
			g_r.horz_wall_content = g_file.map[(int)floor(g_r.check_y / TS)]
												[(int)floor(g_r.check_x / TS)];
			g_r.found_horz_wall_hit = TRUE;
			break ;
		}
		else
		{
			g_r.next_horz_touch_x += g_r.xstep;
			g_r.next_horz_touch_y += g_r.ystep;
		}
	}
}

void	cast_vert_ray(float ray_ang)
{
	g_r.found_vert_wall_hit = FALSE;
	g_r.vert_wall_hit_x = 0;
	g_r.vert_wall_hit_y = 0;
	g_r.vert_wall_content = 0;
	g_r.xintercept = floor(g_ply.ply_x / TS) * TS;
	g_r.xintercept += g_r.is_ray_facing_right ? TS : 0;
	g_r.yintercept = g_ply.ply_y + (g_r.xintercept - g_ply.ply_x)
					* tan(ray_ang);
	g_r.xstep = TS;
	g_r.xstep *= g_r.is_ray_facing_left ? -1 : 1;
	g_r.ystep = TS * tan(ray_ang);
	g_r.ystep *= (g_r.is_ray_facing_up && g_r.ystep > 0) ? -1 : 1;
	g_r.ystep *= (g_r.is_ray_facing_down && g_r.ystep < 0) ? -1 : 1;
	g_r.next_vert_touch_x = g_r.xintercept;
	g_r.next_vert_touch_y = g_r.yintercept;
	find_vert_ray_limit();
}

void	find_vert_ray_limit(void)
{
	while (g_r.next_vert_touch_x >= 0
		&& g_r.next_vert_touch_x <= g_file.map_width * TS
		&& g_r.next_vert_touch_y >= 0
		&& g_r.next_vert_touch_y <= g_file.map_height * TS)
	{
		g_r.check_x = g_r.next_vert_touch_x;
		if (g_r.is_ray_facing_left)
			g_r.check_x -= 1;
		g_r.check_y = g_r.next_vert_touch_y;
		if (rays_map_has_wall_at(g_r.check_x, g_r.check_y))
		{
			g_r.vert_wall_hit_x = g_r.next_vert_touch_x;
			g_r.vert_wall_hit_y = g_r.next_vert_touch_y;
			g_r.vert_wall_content = g_file.map[(int)floor(g_r.check_y / TS)]
												[(int)floor(g_r.check_x / TS)];
			g_r.found_vert_wall_hit = TRUE;
			break ;
		}
		else
		{
			g_r.next_vert_touch_x += g_r.xstep;
			g_r.next_vert_touch_y += g_r.ystep;
		}
	}
}

void	affect_ray_values(float ray_ang, int strip_id)
{
	if (g_r.vert_hit_distance < g_r.horz_hit_distance)
	{
		g_rays[strip_id].distance = g_r.vert_hit_distance;
		g_rays[strip_id].wall_hit_x = g_r.vert_wall_hit_x;
		g_rays[strip_id].wall_hit_y = g_r.vert_wall_hit_y;
		g_rays[strip_id].wall_hit_content = g_r.vert_wall_content;
		g_rays[strip_id].was_hit_ver = TRUE;
	}
	else
	{
		g_rays[strip_id].distance = g_r.horz_hit_distance;
		g_rays[strip_id].wall_hit_x = g_r.horz_wall_hit_x;
		g_rays[strip_id].wall_hit_y = g_r.horz_wall_hit_y;
		g_rays[strip_id].wall_hit_content = g_r.horz_wall_content;
		g_rays[strip_id].was_hit_ver = FALSE;
	}
	g_rays[strip_id].ray_ang = ray_ang;
	g_rays[strip_id].is_ray_down = g_r.is_ray_facing_down;
	g_rays[strip_id].is_ray_up = g_r.is_ray_facing_up;
	g_rays[strip_id].is_ray_left = g_r.is_ray_facing_left;
	g_rays[strip_id].is_ray_right = g_r.is_ray_facing_right;
}
