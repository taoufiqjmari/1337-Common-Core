/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:13:24 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/29 09:50:48 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "cub3d.h"

typedef struct		s_bmp
{
	_Bool			active;
	char			bitmap_signature_bytes[2];
	unsigned int	size_of_bitmap_file;
	unsigned int	reserved_bytes;
	unsigned int	pixel_data_offset;
	unsigned int	size_of_this_header;
	int				width;
	int				height;
	unsigned short	number_of_color_planes;
	unsigned short	color_depth;
	unsigned int	compression_method;
	unsigned int	raw_bitmap_data_size;
	int				horizontal_resolution;
	int				vertical_resolution;
	unsigned int	color_table_entries;
	unsigned int	important_colors;
}					t_bmp;
t_bmp				g_bmp;

int					g_fd;

void				bmp(void);
void				file(void);
void				make_header(void);
void				write_header(void);
void				write_file(void);

#endif
