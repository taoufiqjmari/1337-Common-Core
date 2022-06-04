/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:31:58 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 17:25:21 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reading.h"

void	pre_fc(char **line, char c)
{
	if (c == 'r')
	{
		g_file.r = 1;
		if (ft_strncmp(*line, "R ", 2)
			|| *(*line + 2) == ' ' || *(*line + (g_file.len - 1)) == ' ')
			my_exit("Problem with resolution input.");
	}
	else if (c == 'f')
	{
		g_file.f = 1;
		if (ft_strncmp(*line, "F ", 2)
			|| *(*line + 2) == ' ' || *(*line + (g_file.len - 1)) == ' ')
			my_exit("Problem with floor input.");
		is_info_correct(*line, 'c');
		g_file.part = ft_split(*line, ' ');
	}
	else if (c == 'c')
	{
		g_file.c = 1;
		if (ft_strncmp(*line, "C ", 2)
			|| *(*line + 2) == ' ' || *(*line + (g_file.len - 1)) == ' ')
			my_exit("Problem with ceiling input.");
		is_info_correct(*line, 'c');
		g_file.part = ft_split(*line, ' ');
	}
}

void	in_fc(char c)
{
	if (c == 'f')
	{
		pre_rgb(g_file.rgb, 'r');
		check_rgb_f(*g_file.rgb, 'r');
		pre_rgb(g_file.rgb, 'g');
		check_rgb_f(*(g_file.rgb + 1), 'g');
		pre_rgb(g_file.rgb, 'b');
		check_rgb_f(*(g_file.rgb + 2), 'b');
	}
	else if (c == 'c')
	{
		pre_rgb(g_file.rgb, 'r');
		check_rgb_c(*g_file.rgb, 'r');
		pre_rgb(g_file.rgb, 'g');
		check_rgb_c(*(g_file.rgb + 1), 'g');
		pre_rgb(g_file.rgb, 'b');
		check_rgb_c(*(g_file.rgb + 2), 'b');
	}
}

void	pre_rgb(char **rgb, char c)
{
	char	*temp;

	if (c == 'r')
	{
		is_info_correct(*rgb, 'r');
		temp = *rgb;
		*rgb = ft_strtrim(*rgb, "0");
	}
	if (c == 'g')
	{
		is_info_correct(*(rgb + 1), 'r');
		temp = *(rgb + 1);
		*(rgb + 1) = ft_strtrim(*(rgb + 1), "0");
	}
	if (c == 'b')
	{
		is_info_correct(*(rgb + 2), 'r');
		temp = *(rgb + 2);
		*(rgb + 2) = ft_strtrim(*(rgb + 2), "0");
	}
	free(temp);
}

void	check_rgb_f(char *rgb, char c)
{
	if (ft_strlen(rgb) <= 3)
	{
		if (c == 'r')
		{
			g_fc.f_r = ft_atoi(rgb);
			if (!(g_fc.f_r >= 0 && g_fc.f_r <= 255))
				my_exit("Problem with floor input.");
		}
		else if (c == 'g')
		{
			g_fc.f_g = ft_atoi(rgb);
			if (!(g_fc.f_g >= 0 && g_fc.f_g <= 255))
				my_exit("Problem with floor input.");
		}
		else if (c == 'b')
		{
			g_fc.f_b = ft_atoi(rgb);
			if (!(g_fc.f_b >= 0 && g_fc.f_b <= 255))
				my_exit("Problem with floor input.");
		}
	}
	else
		my_exit("Problem with floor input.");
}

void	check_rgb_c(char *rgb, char c)
{
	if (ft_strlen(rgb) <= 3)
	{
		if (c == 'r')
		{
			g_fc.c_r = ft_atoi(rgb);
			if (!(g_fc.c_r >= 0 && g_fc.c_r <= 255))
				my_exit("Problem with ceiling input.");
		}
		else if (c == 'g')
		{
			g_fc.c_g = ft_atoi(rgb);
			if (!(g_fc.c_g >= 0 && g_fc.c_g <= 255))
				my_exit("Problem with ceiling input.");
		}
		else if (c == 'b')
		{
			g_fc.c_b = ft_atoi(rgb);
			if (!(g_fc.c_b >= 0 && g_fc.c_b <= 255))
				my_exit("Problem with ceiling input.");
		}
	}
	else
		my_exit("Problem with ceiling input.");
}
