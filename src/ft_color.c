/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:08:52 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/03 03:29:22 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

# define		MAX_COLOR	RED
# define		P_MID_COLOR	ORANGE
# define		GND_COLOR	CYAN
# define		N_MID_COLOR	PURPLE
# define		MIN_COLOR	ELECTRIC_ULTRAMARINE

void		ft_fix_color(t_coord *point, t_param *param)
{
	double percent;
	int red;
	int blue;
	int green;

	percent = (double)abs(point->alt) / (double)param->max;
	if (point->alt < 0)
	{
		if (percent < 0.5)
		{
			red =   percent * 2 * (param->n_mid_color >> 16)       + (1.0 - percent * 2) * (param->gnd_color >> 16);
			green = percent * 2 * (param->n_mid_color >> 8 & 0xFF) + (1.0 - percent * 2) * (param->gnd_color >> 8 & 0xFF);
			blue =  percent * 2 * (param->n_mid_color & 0xFF)      + (1.0 - percent * 2) * (param->gnd_color & 0xFF);
		}
		else
		{
			red =   (percent - 0.5) * 2 * (param->min_color >> 16)       + (1.0 - (percent - 0.5) * 2) * (param->n_mid_color >> 16);
			green = (percent - 0.5) * 2 * (param->min_color >> 8 & 0xFF) + (1.0 - (percent - 0.5) * 2) * (param->n_mid_color >> 8 & 0xFF);
			blue =  (percent - 0.5) * 2 * (param->min_color & 0xFF)      + (1.0 - (percent - 0.5) * 2) * (param->n_mid_color & 0xFF);
		}
	}	
	else
	{
		if (percent < 0.5)
		{
			red =   percent * 2 * (param->p_mid_color >> 16)       + (1.0 - percent * 2) * (param->gnd_color >> 16);
			green = percent * 2 * (param->p_mid_color >> 8 & 0xFF) + (1.0 - percent * 2) * (param->gnd_color >> 8 & 0xFF);
			blue =  percent * 2 * (param->p_mid_color & 0xFF)      + (1.0 - percent * 2) * (param->gnd_color & 0xFF);
		}
		else
		{
			red =   (percent - 0.5) * 2 * (param->max_color >> 16)       + (1.0 - (percent - 0.5) * 2) * (param->p_mid_color >> 16);
			green = (percent - 0.5) * 2 * (param->max_color >> 8 & 0xFF) + (1.0 - (percent - 0.5) * 2) * (param->p_mid_color >> 8 & 0xFF);
			blue =  (percent - 0.5) * 2 * (param->max_color & 0xFF)      + (1.0 - (percent - 0.5) * 2) * (param->p_mid_color & 0xFF);
		}
	}
	point->color = red << 16 | green << 8 | blue;
}

void		ft_draw_square(t_coord point, int size, int color,t_all *all)
{
	t_coord	point1;

	point1.y = size;
	while (point1.y--)
	{
		point1.x = size;
		while (point1.x--)
			mlx_pixel_put(all->wdw.mlx_ptr, all->wdw.win_ptr, point1.x + point.x, point1.y + point.y, color);
	}
}
