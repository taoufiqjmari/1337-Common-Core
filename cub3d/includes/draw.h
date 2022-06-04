/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:04:11 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/24 11:44:21 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "cub3d.h"

# define CLICK_LEFT 0
# define CLICK_RIGHT 2
# define CLICK_DOWN 1
# define CLICK_UP 13
# define CLICK_LEFT_VIEW 123
# define CLICK_RIGHT_VIEW 124
# define CLICK_ESC 53

typedef	struct	s_line
{
	int			dx;
	int			dy;
	int			steps;
	float		x_inc;
	float		y_inc;
	float		x;
	float		y;
	int			i;
}				t_line;

void			rect(int i, int j, int color);
void			circle(int i, int j, int color);
void			line(int x1, int y1, int color);
void			put_pixel_to_img(int x, int y, int color);
int				abs(int n);

#endif
