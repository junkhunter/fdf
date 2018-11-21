/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:44:43 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/21 15:32:23 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

static int		ft_open(char **argv)
{
	int fd;

	if (argv[1])
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			write(1, "<Map error>\n", 13);
			return (0);
		}
	}
	else
	{
		write(1, "Usage <filename>\n", 17);
		return (0);
	}
	return (fd);
}

static void		make_title(t_window window)
{
	t_image img;

	img.img = mlx_new_image(window.mlx_ptr, 2550, 120);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size, &img.a);
	img.a = 0;
	while (img.a < 2550 * 100)
		img.data[img.a++] = GRAY;
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_string_put(window.mlx_ptr, window.win_ptr, W_SIZEX / 2 - (ft_strlen("FDF")/2 * 10), 35, BLACK, "FDF");
}

int			main(int argc, char **argv)
{
	int		fd;
	float zoom;
	t_all		all;

	zoom = 2;
	if (argc > 2)
		return (write (1, "usage <filename>\n", 17) & 0);
	all.wdw.mlx_ptr = mlx_init();
	all.wdw.win_ptr = mlx_new_window(all.wdw.mlx_ptr, W_SIZEX, W_SIZEY, "FDF");
	if (!(fd = ft_open(argv)))
		return (0);
	if (!(all.tt.map = init_map(all.wdw, fd, &zoom)))
		return (write(1, "<file error>\n", 13) & 0);
	draw_sqrt(all.wdw, all.tt.map);
	//putimg(all.tt.);
	make_title(all.wdw);
	mlx_key_hook(all.wdw.win_ptr, deal_key, (void *)0);
	//mlx_mouse_hook(window.win_ptr, deal_mouse, tt);
	mlx_loop(all.wdw.mlx_ptr);
}
