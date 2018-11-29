/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:43:17 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/29 21:27:37 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

void	make_change(t_all *all)
{
		calcul_point(all->tt, &all->tt.zoom);
		mlx_destroy_image(all->wdw.mlx_ptr, all->image.img);
		all->image.img = mlx_new_image(all->wdw.mlx_ptr, W_SIZEX, W_SIZEY - 100);
		all->image.data = (int *)mlx_get_data_addr(all->image.img, &all->image.bpp, &all->image.size, &all->image.a);
		draw_sqrt(*all);
		mlx_put_image_to_window(all->wdw.mlx_ptr, all->wdw.win_ptr, all->image.img, 0,100);
}

int			ft_bigger(int val1, int val2)
{
	return ((val1 < val2) ? val2: val1);
}

int			deal_mouse(int button, int x, int y, void *param)
{
	if (button == 5 || button == 4)
	{
		(*(t_all*)param).tt.ecart += -1 * (button == 5) + 1 * (button == 4);
		(*(t_all*)param).tt.ecart = ft_bigger(1, (*(t_all*)param).tt.ecart);
		make_change(param);
	}
/*	ft_putnbr(button);
	ft_putnbr(x);
	ft_putnbr(y);*/
	ft_putendl("ici");
	return(0);
}

int			deal_key(int key, void *param)
{
	ft_putendl("la");
	ft_putnbr(key);
	if (key == 53)
		exit(0);
	else if (key == 126 || key == 125)
	{
		(*(t_all*)param).tt.zoom += -(float)(key == 125) * 0.5 + (float)(key == 126) * 0.5;
		make_change((t_all*)param);
	}
	else if (key == 123 || key == 124)
	{
		(*(t_all*)param).tt.rot += -0.05 * (key == 124) + 0.05 * (key == 123);
		make_change((t_all*)param);
	}
	return (0);
}
