/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:43:17 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/03 03:02:59 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>
#include <stdio.h>

void	make_change(t_all *all)
{
	calcul_point(&all->tt, &all->tt.zoom);
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
	t_param tt;
	
	tt = (*(t_all*)param).tt;
	if (button == 5 || button == 4)
	{
		(*(t_all*)param).tt.ecart += -3 * (button == 5) + 3 * (button == 4);
		(*(t_all*)param).tt.ecart = ft_bigger(1, (*(t_all*)param).tt.ecart);
		/*if (x != W_SIZEX/2 && (*(t_all*)param).tt.ecart != 1)
			(*(t_all*)param).tt.departx += -(x - W_SIZEX / 2) /2 * (button == 5) + (x - W_SIZEX / 2) /2 * (button == 4);
		if (y != (W_SIZEY - 100)/2 && (*(t_all*)param).tt.ecart != 1)
			(*(t_all*)param).tt.departy += -(y - (W_SIZEY - 100) / 2) / 2 / (*(t_all*)param).tt.ecart * (button == 5) + (y - (W_SIZEY - 100) / 2) / (*(t_all*)param).tt.ecart * (button == 4);
		*/
		tt = (*(t_all*)param).tt;
		if (x != tt.centre.x && (*(t_all*)param).tt.ecart != 1)
			(*(t_all*)param).tt.departx += (x - tt.centre.x) / 3.5 * (button == 5) + -(x - tt.centre.x) / 3.5 * (button == 4);
		if (y != tt.centre.y && (*(t_all*)param).tt.ecart != 1)
			(*(t_all*)param).tt.departy += (y - (tt.centre.y)) / 3.5 * (button == 5) + -(y - (tt.centre.y)) / 3.5 * (button == 4);
		
		printf("modif x -> %d\nmodif y -> %d\n", (x - tt.centre.x) / 3 * (button == 5) + -(x - tt.centre.x) / 3 * (button == 4) ,
		 -(y - (tt.centre.y)) / 10 * (button == 5) + (y - (tt.centre.x)) / 10 * (button == 4));
		make_change(param);
	}
	else if (button == 1)
	{
		if (!((t_all*)param)->press)
			((t_all*)param)->press = 1;
		else
			((t_all*)param)->press = 0;
		((t_all*)param)->last_y = y;
		((t_all*)param)->last_x = x;
	}
	//else if (button == 2)
	//	((t_all*)param)->press  = 0;
	/*	ft_putnbr(button);
		ft_putnbr(x);
		ft_putnbr(y);*/
	//	ft_putendl("ici");
	return (0);
}
#include <math.h>
int			deal_key(int key, void *param)
{
	//	ft_putendl("la");
	//	ft_putnbr(key);
	t_all param_cl;

	param_cl = *(t_all*)param;
	if (key == 53)
		exit(0);
	else if (key == 126 || key == 125)
	{
		(*(t_all*)param).tt.zoom += -(float)(key == 125) * 0.5 + (float)(key == 126) * 0.5;
		make_change((t_all*)param);
	}
	else if (key == 123 || key == 124)
	{
		((t_all*)param)->tt.rot += -0.05 * (key == 124) + 0.05 * (key == 123);
		//(*(t_all*)param).tt.departx += -5 * (key == 124) + 5 * (key == 123);
		make_change(param);
		printf("sin(%lf) = %lf\ncos(%lf) = %lf\n", ((t_all*)param)->tt.rot, sin(((t_all*)param)->tt.rot), ((t_all*)param)->tt.rot, cos(((t_all*)param)->tt.rot));

		//printf("key_rotate %lf\n", ((t_all*)param)->tt.rot);
	}
	return (0);
}

int			deal_mouse2(int x, int y, void *param)
{
	t_all *fdf;

	if (((t_all*)param)->press == 1)
	{
		fdf = (t_all*)param;
		fdf->tt.departx -= fdf->last_x - x;
		fdf->tt.departy -= fdf->last_y - y;
		fdf->last_x = x;
		fdf->last_y = y;
		make_change((t_all*)param);
	}
	//printf("x -> %d y -> %d\n", x, y);
	return (0);
}

int			release_btn(int button, int x, int y, void *param)
{
	if (button == 1)
	{
		((t_all*)param)->press  = 0;
		((t_all*)param)->last_y = -200;
		((t_all*)param)->last_x = -200;
	}
	return (0);
}
