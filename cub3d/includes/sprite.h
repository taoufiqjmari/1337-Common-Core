/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:09:39 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 11:09:42 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

typedef struct	s_sprite
{
	int			count;
	char		*texture;
	void		*txt;
	int			*texel;
	int			w;
	int			h;
	int			color;
	int			bpp;
	int			line_length;
	int			endian;
}				t_sprite;
t_sprite		g_sprite;

typedef struct	s_sprites
{
	int			x;
	int			y;
	float		distance;
	float		angle;
}				t_sprites;
t_sprites		*g_sprites;

void			sprite(int i, int j);
void			salloc(void);
void			sprite_data(void);
void			put_data(int i, int j);
void			get_distance(void);
void			render_sprite(void);
void			ft_sort(void);
void			draw_sprite(int x, float distance, float strip_h);
void			put_spixel_to_img(int x, int y);

#endif
