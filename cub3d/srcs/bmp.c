/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:13:27 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/29 11:52:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bmp.h"

void	file(void)
{
	if (!(g_fd = open("screenshot.bmp", O_WRONLY | O_CREAT, S_IRUSR
						| S_IWUSR | S_IRGRP | S_IROTH)))
		my_exit("Problem with bitmap file.");
}

void	make_header(void)
{
	g_bmp.bitmap_signature_bytes[0] = 'B';
	g_bmp.bitmap_signature_bytes[1] = 'M';
	g_bmp.size_of_bitmap_file = (g_mlx.win_w *
					g_mlx.win_h * 3) + 54;
	g_bmp.reserved_bytes = 0;
	g_bmp.pixel_data_offset = 54;
	g_bmp.size_of_this_header = 40;
	g_bmp.width = g_mlx.win_w;
	g_bmp.height = -g_mlx.win_h;
	g_bmp.number_of_color_planes = 1;
	g_bmp.color_depth = 32;
	g_bmp.compression_method = 0;
	g_bmp.raw_bitmap_data_size = (g_mlx.win_w * g_mlx.win_h * 4);
	g_bmp.horizontal_resolution = 3780;
	g_bmp.vertical_resolution = 3780;
	g_bmp.color_table_entries = 0;
	g_bmp.important_colors = 0;
}

void	write_header(void)
{
	write(g_fd, &g_bmp.bitmap_signature_bytes, 2);
	write(g_fd, &g_bmp.size_of_bitmap_file, 4);
	write(g_fd, &g_bmp.reserved_bytes, 4);
	write(g_fd, &g_bmp.pixel_data_offset, 4);
	write(g_fd, &g_bmp.size_of_this_header, 4);
	write(g_fd, &g_bmp.width, 4);
	write(g_fd, &g_bmp.height, 4);
	write(g_fd, &g_bmp.number_of_color_planes, 2);
	write(g_fd, &g_bmp.color_depth, 2);
	write(g_fd, &g_bmp.compression_method, 4);
	write(g_fd, &g_bmp.raw_bitmap_data_size, 4);
	write(g_fd, &g_bmp.horizontal_resolution, 4);
	write(g_fd, &g_bmp.vertical_resolution, 4);
	write(g_fd, &g_bmp.color_table_entries, 4);
	write(g_fd, &g_bmp.important_colors, 4);
}

void	write_file(void)
{
	char				*pixel_array;
	unsigned int		i;
	int					j;

	if (!(pixel_array = malloc(sizeof(char) * g_bmp.raw_bitmap_data_size)))
		my_exit("Problem with bitmap file.");
	i = 0;
	j = 0;
	g_bmp.raw_bitmap_data_size /= 4;
	while (i < g_bmp.raw_bitmap_data_size)
	{
		pixel_array[j++] = g_mlx.addr[i] & 255;
		pixel_array[j++] = (g_mlx.addr[i] & 255 << 8) >> 8;
		pixel_array[j++] = (g_mlx.addr[i] & 255 << 16) >> 16;
		j++;
		i++;
	}
	write(g_fd, pixel_array, g_bmp.raw_bitmap_data_size *= 4);
	free(pixel_array);
}

void	bmp(void)
{
	ft_bzero(&g_bmp, sizeof(t_bmp));
	file();
	make_header();
	write_header();
	write_file();
	close(g_fd);
}
