/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:42:06 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/02 22:36:31 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"

void	img_put_pixel(int *img, t_coord point, int size, int color)
{
		if (point.y > 100 && point.y < W_SIZEY &&
		point.x >= 0 && point.x <= W_SIZEX)
		img[(point.y - 100) * W_SIZEX + point.x] = color;
}

/*void	reset_img(t_image image)
{
	while (image.size--)
		image.data[image.size] = 0;
}
*/
void    draw_sqrt(t_all all)
{
	int		i;

	while (all.tt.map && !(i = 0))
	{
		while (i < all.tt.map->size)
		{
			//img_put_pixel(all.image.data, all.tt.map->point[i], all.image.size, all.tt.map->point[i].color/*delta_color(nb , point1, point2, var.dx)*/);
			
			if (i < all.tt.map->size - 1 && all.tt.map->point[i].x < W_SIZEX && all.tt.map->point[i].y < W_SIZEY
					&& all.tt.map->point[i + 1].x < W_SIZEX && all.tt.map->point[i + 1].y < W_SIZEY)
			{
				
				if (all.tt.map->point[i].alt <= all.tt.map->point[i + 1].alt)
					draw_line(all.tt.map->point[i], all.tt.map->point[i + 1], all, all.tt.ecart);
				else
					draw_line(all.tt.map->point[i + 1], all.tt.map->point[i], all , all.tt.ecart);
			}
			if (all.tt.map->next != NULL && all.tt.map->point[i].x < W_SIZEX && all.tt.map->point[i].y < W_SIZEY
					&& all.tt.map->next->point[i].x < W_SIZEX && all.tt.map->next->point[i].y < W_SIZEY)
			{
				if (all.tt.map->point[i].alt <= all.tt.map->next->point[i].alt)
					draw_line(all.tt.map->point[i], all.tt.map->next->point[i], all , all.tt.ecart);
				else
					draw_line(all.tt.map->next->point[i], all.tt.map->point[i], all , all.tt.ecart);
			}
			i++;
		}
		all.tt.map = all.tt.map->next;
	}
}

void		init_var_draw(t_var_draw *var, t_coord point1, t_coord point2)
{
	var->dx = abs(point2.x-point1.x);
	var->dy = abs(point2.y-point1.y);
	var->xincr = (point1.x < point2.x) ? 1 : -1;
	var->yincr = (point1.y < point2.y) ? 1 : -1;
	var->erreur = (var->dx > var->dy) ? var->dx / 2 : var->dy /2;
	var->e = 0;
}

#include <unistd.h>

void		print_bit(int color)
{
	int i;

	i = 32;
	while (i-- > 0)
	{
		if (i % 8 == 0 && i < 31)
			write(1, " ", 1);
		write (1, (color & (1 << i)) ? "1": "0", 1);
	}
}

int			delta_color(float percent, t_coord point1, t_coord point2, int size_l)
{
	int red;
	int blue;
	int green;

	red = 0;
	blue = 0;
	green = 0;
	if (((point1.color >> 16) & 0xFF) < ((point2.color >> 16) & 0xFF))
		red = ((point1.color >> 16) & 0X0000FF) + (((point2.color >> 16) & 0X0000FF) - ((point1.color >> 16) & 0X0000FF)) * percent;
	else	
		red = ((point1.color >> 16) & 0X0000FF) - (((point1.color >> 16) & 0X0000FF) - ((point2.color >> 16) & 0X0000FF)) * percent;
	if (((point1.color >> 8) & 0xFF) < ((point2.color >> 8) & 0xFF))
		green = ((point1.color >> 8) & 0X0000FF) + (((point2.color >> 8) & 0X0000FF) - ((point1.color >> 8) & 0X0000FF)) * percent;
	else
		green = ((point1.color >> 8) & 0X0000FF) - (((point1.color >> 8) & 0X0000FF) - ((point2.color >> 8) & 0X0000FF)) * percent;
	if (((point1.color) & 0xFF) < ((point2.color) & 0xFF))
		blue = (point1.color & 0X0000FF) + (((point2.color & 0X0000FF) - (point1.color & 0X0000FF)) * percent);
	else
		blue = (point1.color & 0X0000FF) - (((point1.color & 0X0000FF) - (point2.color & 0X0000FF)) * percent);
	return ((red << 16) | (green << 8) | (blue));
}

void		draw_line(t_coord point1, t_coord point2, t_all all, int ecart)
{
	t_var_draw	var;
	float		nb;
	int color;
	int size_l;

	init_var_draw(&var, point1, point2);
	size_l = sqrt(pow(var.dx, 2) + pow(var.dy, 2));
	if (var.dx > var.dy)
	{
		while ((var.e++) < var.dx)
		{
			point1.x += var.xincr;
			var.erreur += var.dy;
			if (var.erreur > var.dx)
			{
				var.erreur -= var.dx;
				point1.y += var.yincr;
			}
			nb = ((float)(float)var.e / (float)size_l);
			if (point1.color != point2.color)
				color = delta_color(nb, point1, point2, size_l);
			else if (color != point1.color)
				color = point1.color;
			img_put_pixel(all.image.data, point1, all.image.size, color);
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
			nb = ((float)(float)var.e / (float)size_l);
			if (point1.color != point2.color)
				color = delta_color(nb, point1, point2, size_l);
			else if (color != point1.color)
				color = point1.color;
						img_put_pixel(all.image.data, point1, all.image.size, color);
		}
	}
}
