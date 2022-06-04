/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 17:43:56 by tjmari            #+#    #+#             */
/*   Updated: 2021/01/28 18:25:42 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	arguments(int argc, char **argv)
{
	int		len;

	if (argc >= 2 && argc <= 3)
	{
		len = ft_strlen(argv[1]);
		if ((g_file.fd = open(argv[1], O_RDONLY)) == -1
			|| (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c'
			|| argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b'))
			my_exit("Problem with info file.");
		g_bmp.active = 0;
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7))
				my_exit("Did you mean '--save'?");
			g_bmp.active = 1;
		}
	}
	else
		my_exit("Wrong number of arguments");
}

void	setup(void)
{
	if (!(g_mlx.mlx_win = mlx_new_window(g_mlx.mlx, g_mlx.win_w,
											g_mlx.win_h, "cub3D")))
		my_exit("Problem with mlx_new_window()");
	if (!(g_mlx.img = mlx_new_image(g_mlx.mlx,
										g_mlx.win_w, g_mlx.win_h)))
		my_exit("Problem with mlx_new_image()");
	if (!(g_mlx.addr = (int *)mlx_get_data_addr(g_mlx.img,
		&g_mlx.bits_per_pixel, &g_mlx.line_length, &g_mlx.endian)))
		my_exit("Problem with mlx_get_data_addr()");
	g_ply.turn_direction = 0;
	g_ply.walk_direction = 0;
	g_ply.move_speed = 20.0;
	g_ply.rotation_speed = rad(10);
	g_dis_proj_plane = (g_mlx.win_w / 2) / tan(FOV_ANG / 1.5);
	textures();
	salloc();
	sprite_data();
}

void	render(void)
{
	update_player();
	update_rays();
	render_3d();
	render_map();
	render_rays();
	render_player();
	render_sprite();
	if (g_bmp.active)
	{
		bmp();
		my_exit_clean("Screenshot saved.");
	}
	mlx_put_image_to_window(g_mlx.mlx, g_mlx.mlx_win, g_mlx.img, 0, 0);
}

int		main(int argc, char **argv)
{
	if (!(g_mlx.mlx = mlx_init()))
		my_exit("Problem with mlx_init()");
	arguments(argc, argv);
	reading_file();
	final_map();
	map_parsing();
	setup();
	render();
	mlx_hook(g_mlx.mlx_win, 2, 1L << 0, key_pressed, &g_ply);
	mlx_hook(g_mlx.mlx_win, 17, 0L, red_cross, &g_mlx);
	mlx_loop(g_mlx.mlx);
	return (EXIT_SUCCESS);
}
