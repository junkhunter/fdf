/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 15:44:43 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/19 00:43:37 by rhunders         ###   ########.fr       */
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
			write(1, "<Map error>\n", 13); //ne s'affiche pas
			return (0);
		}
	}
	else
	{
		write (1, "Usage <filename>\n", 17);
		return (0);
	}
	return (fd);
}

void	make_titre(t_window window)
{
	t_image img;

	img.img = mlx_new_image(window.mlx_ptr, 2550, 100);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.size, &img.a);
	img.a = 0;
	while (img.a < 2550 * 100)
		img.data[img.a++] = GRAY;
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img, 0, 0);
	mlx_string_put(window.mlx_ptr, window.win_ptr, W_SIZEX / 2 - (ft_strlen("FDF")/2 * 10), 45, DARK_BROWN, "FDF");
}

int		main(int argc, char **argv)
{
	t_window window;
	t_line	*map;
	int		fd;
	float zoom;

	zoom = 2;
	if (argc > 2)
		return (write (1, "usage <filename>\n", 17) & 0);
	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, W_SIZEX, W_SIZEY, "FDF");
	if (!(fd = ft_open(argv)))
		return (0);
	if (!(map = init_map(window, fd, &zoom)))
		return (write(1, "<file error>\n", 13) & 0);
	draw_sqrt(window, map);
	make_titre(window);
	mlx_key_hook(window.win_ptr, deal_key, map);
	//mlx_mouse_hook(window.win_ptr, deal_mouse, map);
	mlx_loop(window.mlx_ptr);
}
