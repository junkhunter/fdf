/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:43:17 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/19 00:47:31 by rhunders         ###   ########.fr       */
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
	ft_putnbr(key);
	if (key == 53)
		exit(0);
	else if (key == 126 || key == 125)
	{
		if (((t_line*)param)->zoom > 0 || key == 126)
			((t_line*)param)->zoom += -1 + ((key - 125) * 2);
		//calcul_point(param, ((t_line*)param)->zoom, ((t_line*)param)->ecart);
	}
	/*else if (key == 125)
	{
		*(int*)param -= 1;
	}*/
	return (0);
}
