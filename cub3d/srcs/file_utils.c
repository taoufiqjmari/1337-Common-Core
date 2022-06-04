/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:24:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/29 10:34:18 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reading.h"

void	elements(char *line)
{
	if (*line == 'R')
		validate_r(line);
	else if (*line == 'N')
		validate_no(line);
	else if (*line == 'S')
	{
		if (*(line + 1) == 'O')
			validate_so(line);
		else
			validate_s(line);
	}
	else if (*line == 'W')
		validate_we(line);
	else if (*line == 'E')
		validate_ea(line);
	else if (*line == 'F')
		validate_f(line);
	else if (*line == 'C')
		validate_c(line);
	else if (*line == '\0')
		return ;
	else
		my_exit("Error in file");
}

void	on_map(char **line)
{
	char	*temp;

	if (**line == '\0' && !g_file.start_map)
		return ;
	else if (**line != '\0')
	{
		g_file.start_map = 1;
		temp = g_file.temp_map;
		g_file.temp_map = ft_strjoin(g_file.temp_map, "\n");
		free(temp);
		temp = g_file.temp_map;
		g_file.temp_map = ft_strjoin(g_file.temp_map, *line);
		free(temp);
		if (g_file.map_width < ft_strlen(*line))
			g_file.map_width = ft_strlen(*line);
		g_file.map_height++;
	}
	else
		my_exit("Either a newline inside map or at the end of map \
				\nor an element is duplicated.");
}
