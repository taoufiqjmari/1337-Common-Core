/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:14:33 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 11:29:13 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

void	render_map(void);
void	map(int tile_x, int tile_y, int i, int j);
void	sprite_2d(int tile_x, int tile_y);

#endif
