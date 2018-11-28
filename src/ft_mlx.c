/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:43:17 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/28 17:07:52 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

int			deal_mouse(int button, int x, int y, void *param)
{
	t_image	img;

/*	if (button == 5 || button == 4)
	{
		((t_param*)param)->map->zoom += -1 + ((button - 4) * 2);
		calcul_point(((t_param*)param)->map,
			   	((t_param*)param)->ecart, ((t_param*)param)->zoom);
		img.img = mlx_new_image(((t_param*)param)->window.mlx_ptr,
			((t_param*)param)->window.win_ptr,W_SIZEX,
		   	W_SIZEY - 100);
		img.data = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.size, &img.a);
		img.a = 0;
		//while (img.a)
	}*/
	ft_putnbr(button);
	ft_putnbr(x);
	ft_putnbr(y);
	ft_putendl("");
	return(0);
}

int			deal_key(int key, void *param)
{
	t_all all;

	all = *((t_all*)param);
	ft_putnbr(key);
	if (key == 53)
		exit(0);
	else if (key == 126 || key == 125)
	{
		if (all.tt.zoom > 0 || key == 126)
			all.tt.zoom += -1 + ((key - 125) * 2);
		calcul_point(all.tt, all.tt.ecart, &all.tt.zoom);
		draw_sqrt(all);
		mlx_put_image_to_window(all.wdw.mlx_ptr, all.wdw.win_ptr, all.image.img, 0,100);
	}
	/*else if (key == 125)
	{
		*(int*)param -= 1;
	}*/
	return (0);
}
