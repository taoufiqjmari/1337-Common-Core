/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:27:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 17:28:05 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reading.h"

void	validate_no(char *line)
{
	size_t	len;
	char	**part;

	len = ft_strlen(line);
	if (!g_file.no)
	{
		g_file.no = 1;
		if (ft_strncmp(line, "NO ", 3)
			|| *(line + 3) == ' ' || *(line + (len - 1)) == ' ')
			my_exit("Problem with north texture input.");
		part = ft_split(line, ' ');
		if (how_many_part(part) == 2)
		{
			if (!(g_texture.txt[0] = mlx_xpm_file_to_image(g_mlx.mlx, part[1],
				&g_texture.w[0], &g_texture.h[0])))
				my_exit("Problem with north texture input.");
		}
		else
			my_exit("Problem with north texture input.");
		free_dpointer(part);
	}
	else
		my_exit("Problem with north texture input.");
}

void	validate_so(char *line)
{
	size_t	len;
	char	**part;

	len = ft_strlen(line);
	if (!g_file.so)
	{
		g_file.so = 1;
		if (ft_strncmp(line, "SO ", 3)
			|| *(line + 3) == ' ' || *(line + (len - 1)) == ' ')
			my_exit("Problem with south texture input.");
		part = ft_split(line, ' ');
		if (how_many_part(part) == 2)
		{
			if (!(g_texture.txt[1] = mlx_xpm_file_to_image(g_mlx.mlx, part[1],
				&g_texture.w[1], &g_texture.h[1])))
				my_exit("Problem with south texture input.");
		}
		else
			my_exit("Problem with south texture input.");
		free_dpointer(part);
	}
	else
		my_exit("Problem with south texture input.");
}

void	validate_we(char *line)
{
	size_t	len;
	char	**part;

	len = ft_strlen(line);
	if (!g_file.we)
	{
		g_file.we = 1;
		if (ft_strncmp(line, "WE ", 3)
			|| *(line + 3) == ' ' || *(line + (len - 1)) == ' ')
			my_exit("Problem with west texture input.");
		part = ft_split(line, ' ');
		if (how_many_part(part) == 2)
		{
			if (!(g_texture.txt[2] = mlx_xpm_file_to_image(g_mlx.mlx, part[1],
				&g_texture.w[2], &g_texture.h[2])))
				my_exit("Problem with west texture input.");
		}
		else
			my_exit("Problem with west texture input.");
		free_dpointer(part);
	}
	else
		my_exit("Problem with west texture input.");
}

void	validate_ea(char *line)
{
	size_t	len;
	char	**part;

	len = ft_strlen(line);
	if (!g_file.ea)
	{
		g_file.ea = 1;
		if (ft_strncmp(line, "EA ", 3)
			|| *(line + 3) == ' ' || *(line + (len - 1)) == ' ')
			my_exit("Problem with east texture input.");
		part = ft_split(line, ' ');
		if (how_many_part(part) == 2)
		{
			if (!(g_texture.txt[3] = mlx_xpm_file_to_image(g_mlx.mlx, part[1],
				&g_texture.w[3], &g_texture.h[3])))
				my_exit("Problem with east texture input.");
		}
		else
			my_exit("Problem with east texture input.");
		free_dpointer(part);
	}
	else
		my_exit("Problem with east texture input.");
}

void	validate_s(char *line)
{
	size_t	len;
	char	**part;

	len = ft_strlen(line);
	if (!g_file.s)
	{
		g_file.s = 1;
		if (ft_strncmp(line, "S ", 2)
			|| *(line + 2) == ' ' || *(line + (len - 1)) == ' ')
			my_exit("Problem with sprite texture input.");
		part = ft_split(line, ' ');
		if (how_many_part(part) == 2)
		{
			if (!(g_sprite.txt = mlx_xpm_file_to_image(g_mlx.mlx, part[1],
				&g_sprite.w, &g_sprite.h)))
				my_exit("Problem with sprite texture input.");
		}
		else
			my_exit("Problem with sprite texture input.");
		free_dpointer(part);
	}
	else
		my_exit("Problem with sprite texture input.");
}
