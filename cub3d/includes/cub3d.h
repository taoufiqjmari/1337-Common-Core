/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:46:38 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 17:31:04 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "../libft/libft.h"
# include "reading.h"
# include "map.h"
# include "player.h"
# include "rays.h"
# include "three.h"
# include "sprite.h"
# include "bmp.h"
# include "angles.h"
# include "draw.h"

# define FALSE 0
# define TRUE 1

# define MINIMAP_SCALE_FACTOR 0.2
# define TS 64

typedef	struct	s_mlx
{
	void		*mlx;
	void		*mlx_win;
	int			win_w;
	int			win_h;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;
t_mlx			g_mlx;

void			arguments(int argc, char **argv);
void			setup(void);
void			render(void);
void			my_exit(const char *str);
void			my_exit_clean(const char *str);
int				red_cross(void);

#endif
