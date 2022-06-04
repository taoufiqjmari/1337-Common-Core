/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:19:12 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 17:23:59 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reading.h"

void	res_util(char **part, char *temp, char c)
{
	is_info_correct(*part, 'r');
	temp = *part;
	*part = ft_strtrim(*part, "0");
	free(temp);
	if (c == 'w')
	{
		if (ft_strlen(*part) > 4)
			g_mlx.win_w = 2560;
		else
		{
			g_mlx.win_w = atoi(*part);
			g_mlx.win_w = g_mlx.win_w > 2560 ? 2560 : g_mlx.win_w;
		}
	}
	else if (c == 'h')
	{
		if (ft_strlen(*part) > 4)
			g_mlx.win_h = 1440;
		else
		{
			g_mlx.win_h = atoi(*part);
			g_mlx.win_h = g_mlx.win_h > 1440 ? 1440 : g_mlx.win_h;
		}
	}
}

void	validate_r(char *line)
{
	char	*temp;

	temp = NULL;
	g_file.len = ft_strlen(line);
	if (!g_file.r)
	{
		g_file.part = ft_split(line, ' ');
		pre_fc(&line, 'r');
		if (how_many_part(g_file.part) == 3)
		{
			res_util(g_file.part + 1, temp, 'w');
			res_util(g_file.part + 2, temp, 'h');
		}
		else
			my_exit("Problem with resolution input.");
		free_dpointer(g_file.part);
	}
	else
		my_exit("Problem with resolution input.");
}

void	validate_f(char *line)
{
	g_file.len = ft_strlen(line);
	if (!g_file.f)
	{
		pre_fc(&line, 'f');
		if (how_many_part(g_file.part) == 2)
		{
			g_file.rgb = ft_split(*(g_file.part + 1), ',');
			if (how_many_part(g_file.rgb) == 3)
			{
				in_fc('f');
				g_fc.f = g_fc.f_r << 16 | g_fc.f_g << 8 | g_fc.f_b;
			}
			else
				my_exit("Problem with resolution input.");
			free_dpointer(g_file.rgb);
		}
		else
			my_exit("Problem with floor input.");
		free_dpointer(g_file.part);
	}
	else
		my_exit("Problem with floor input.");
}

void	validate_c(char *line)
{
	g_file.len = ft_strlen(line);
	if (!g_file.c)
	{
		pre_fc(&line, 'c');
		if (how_many_part(g_file.part) == 2)
		{
			g_file.rgb = ft_split(*(g_file.part + 1), ',');
			if (how_many_part(g_file.rgb) == 3)
			{
				in_fc('c');
				g_fc.c = g_fc.c_r << 16 | g_fc.c_g << 8 | g_fc.c_b;
			}
			else
				my_exit("Problem with ceiling input.");
			free_dpointer(g_file.rgb);
		}
		else
			my_exit("Problem with ceiling input.");
		free_dpointer(g_file.part);
	}
	else
		my_exit("Problem with ceiling input.");
}

void	textures(void)
{
	g_texture.texel[0] = (int *)mlx_get_data_addr(g_texture.txt[0],
			&g_texture.bpp, &g_texture.line_length, &g_texture.endian);
	g_texture.texel[1] = (int *)mlx_get_data_addr(g_texture.txt[1],
			&g_texture.bpp, &g_texture.line_length, &g_texture.endian);
	g_texture.texel[2] = (int *)mlx_get_data_addr(g_texture.txt[2],
			&g_texture.bpp, &g_texture.line_length, &g_texture.endian);
	g_texture.texel[3] = (int *)mlx_get_data_addr(g_texture.txt[3],
			&g_texture.bpp, &g_texture.line_length, &g_texture.endian);
	g_sprite.texel = (int *)mlx_get_data_addr(g_sprite.txt,
			&g_sprite.bpp, &g_sprite.line_length, &g_sprite.endian);
}
