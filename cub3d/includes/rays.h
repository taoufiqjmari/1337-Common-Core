/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:00:17 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/27 14:55:47 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYS_H
# define RAYS_H

# include "cub3d.h"

typedef	struct	s_ray
{
	float		ray_ang;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	_Bool		was_hit_ver;
	_Bool		is_ray_up;
	_Bool		is_ray_down;
	_Bool		is_ray_left;
	_Bool		is_ray_right;
	int			wall_hit_content;
}				t_rays;
t_rays			g_rays[2560];

typedef	struct	s_r
{
	int			is_ray_facing_down;
	int			is_ray_facing_up;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
	float		xintercept;
	float		yintercept;
	float		xstep;
	float		ystep;
	float		next_horz_touch_x;
	float		next_horz_touch_y;
	float		next_vert_touch_x;
	float		next_vert_touch_y;
	float		check_x;
	float		check_y;
	int			found_horz_wall_hit;
	float		horz_wall_hit_x;
	float		horz_wall_hit_y;
	int			horz_wall_content;
	float		horz_hit_distance;
	int			found_vert_wall_hit;
	float		vert_wall_hit_x;
	float		vert_wall_hit_y;
	int			vert_wall_content;
	float		vert_hit_distance;
}				t_r;
t_r				g_r;

void			update_rays(void);
void			cast_ray(float ray_ang, int strip_id);
void			cast_horz_ray(float ray_ang);
void			find_horz_ray_limit(void);
void			cast_vert_ray(float ray_ang);
void			find_vert_ray_limit(void);
void			affect_ray_values(float ray_ang, int strip_id);
_Bool			rays_map_has_wall_at(float new_x, float new_y);
float			pythagore(float x1, float y1, float x2, float y2);
void			render_rays(void);

#endif
