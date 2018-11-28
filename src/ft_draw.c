/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:43:22 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/28 16:22:23 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

void	img_put_pixel(int *img, t_coord point)
{
	img[(point.y - 100) * W_SIZEX + point.x] = point.color;
}

void	reset_img(t_image image)
{
	while (image.size--)
	{
		image.data[image.size] = 0;
	}
}

void    draw_sqrt(t_all all, t_line *lst_map)
{
	int		i;

	reset_img(all.image);
	while (lst_map)
	{
		i = 0;
		while(i < lst_map->size)
		{
			if (i < lst_map->size - 1 && lst_map->point[i].x < W_SIZEX && lst_map->point[i].y < W_SIZEY
					&& lst_map->point[i + 1].x < W_SIZEX && lst_map->point[i + 1].y < W_SIZEY)
			{
				if (lst_map->point[i].alt <= lst_map->point[i + 1].alt)
					draw_line(lst_map->point[i], lst_map->point[i + 1], all, lst_map->ecart);
				else
					draw_line(lst_map->point[i + 1], lst_map->point[i], all , lst_map->ecart);
			}
			if (lst_map->next != NULL && lst_map->point[i].x < W_SIZEX && lst_map->point[i].y < W_SIZEY
					&& lst_map->next->point[i].x < W_SIZEX && lst_map->next->point[i].y < W_SIZEY)
			{
				if (lst_map->point[i].alt <= lst_map->next->point[i].alt)
					draw_line(lst_map->point[i], lst_map->next->point[i], all , lst_map->ecart);
				else
					draw_line(lst_map->next->point[i], lst_map->point[i], all , lst_map->ecart);
			}
			i++;
		}
		lst_map = lst_map->next;
	}
}

void		init_var_draw(t_var_draw *var, t_coord point1, t_coord point2, int *size_l)
{
	var->dx = abs(point2.x-point1.x);
	var->dy = abs(point2.y-point1.y);
	var->xincr = (point1.x < point2.x) ? 1 : -1;
	var->yincr = (point1.y < point2.y) ? 1 : -1;
	var->erreur = (var->dx > var->dy) ? var->dx / 2 : var->dy /2;
	var->e = 0;
	*size_l = sqrt(pow(var->dx, 2) + pow(var->dy, 2));
}

int			delta_color(int col1 , int col2, int inc, int size_l)
{
	int i;

	i = -1;
	if (col1 > col2)
		while (++i < size_l && col1 > col2)
			col1 += inc;
	else
		while (++i < size_l && col1 < col2)
			col1 += inc;
	return ((i < size_l) ? i : 0);
}

void		draw_line(t_coord point1, t_coord point2, t_all all , int ecart)
{
	t_var_draw	var;
	int			inc;
	int			size_l;
	int			d_color;

	init_var_draw(&var, point1, point2, &size_l);
	inc = (point2.alt > 128 || point2.alt < 0) ?
		ft_select_increment(point2) : -0X000002;
	//d_color = delta_color(point1.color, point2.color, inc, size_l);
	d_color = point1.color > point2.color;
	//if (d_color)
	//	printf ("%d\n",d_color);
	//if ((point1.color != point2.color) || (d_color = 0))
	//	d_color = /*(size_l / */(point2.color - point1.color)/*)*/ / inc;
	if (var.dx > var.dy)
	{
		while ((var.e++) < var.dx)
		{
			point1.x += var.xincr;
			var.erreur += var.dy;
			if (var.erreur > var.dx)
			{
				//	if (point2.alt != point1.alt && point2.alt > -255)
				//		if (size_l <= 255 || (var.e % 2 == 0))
				//			point1.color += inc;
				var.erreur -= var.dx;
				point1.y += var.yincr;
			}
			if (point2.alt > 255 * 2)
				point1.color = 0XFFFFFF;
			//if ()
			//	point1.color += inc;
			//else
			//	if (point2.alt != point1.alt && point1.color < point2.color)
			//		point1.color += inc;*/
			//if (point1.color > point2.color)
			//	point1.color = point2.color;
			img_put_pixel(all.image.data, point1);
		}
	}
	else
	{
		while (var.e++ < var.dy)
		{
			point1.y += var.yincr;
			var.erreur += var.dx;
			if (var.erreur > var.dy)
			{
				var.erreur -= var.dy;
				point1.x += var.xincr;
			}
			if (point2.alt > 256 * 2)
				point1.color = 0XFFFFFF;
			else if (point1.alt != point2.alt && (!d_color || !(var.e % d_color)))
				point1.color += inc;
			//if (point2.alt != point1.alt)
			//if (point1.color > point2.color)
			//	point1.color = point2.color;
			//	point1.color += inc;
			img_put_pixel(all.image.data, point1);
		}
	}
}
