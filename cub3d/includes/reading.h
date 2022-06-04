/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:42:03 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 16:17:24 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include "cub3d.h"

# define BUFFER_SIZE 100

typedef struct	s_file
{
	int			fd;
	_Bool		r;
	_Bool		no;
	_Bool		so;
	_Bool		we;
	_Bool		ea;
	_Bool		s;
	_Bool		f;
	_Bool		c;
	_Bool		read;
	_Bool		start_map;
	char		*temp_map;
	char		**map_splitted;
	char		**map;
	size_t		map_width;
	size_t		map_height;
	size_t		len;
	char		**part;
	char		**rgb;
}				t_file;
t_file			g_file;

void			reading_file(void);
void			elements(char *line);
void			on_map(char **line);
void			init_elements(void);
int				get_next_line(int fd, char **line);
void			validate_r(char *line);
void			res_util(char **part, char *temp, char c);
void			validate_no(char *line);
void			validate_so(char *line);
void			validate_we(char *line);
void			validate_ea(char *line);
void			validate_s(char *line);
void			textures(void);
void			validate_f(char *line);
void			check_rgb_f(char *rgb, char c);
void			validate_c(char *line);
void			check_rgb_c(char *rgb, char c);
void			pre_rgb(char **rgb, char c);
void			pre_fc(char **line, char c);
void			in_fc(char c);
void			is_info_correct(char *part, char c);
int				how_many_part(char **part);
void			all_read(void);
void			final_map(void);
void			map_parsing(void);
void			to_check(size_t i, size_t j);
int				splitted_to(char **str);
void			free_dpointer(char **str);

#endif
