/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 01:51:30 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/03 02:42:43 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include <math.h>

#define limit 255

void        init_point(t_coord *point)
{
	point->x = DEPARTX;
	point->y = DEPARTY;
}

void		set_point(t_coord *current, t_param *param)
{
	int i;
	i = -1;

	while (++i < param->map->size)
	{
		//param->map->point[i].alt = ;
		//param->map->point[i].x = current->x - param->map->point[i].alt/10 * cos(param->b);
		//param->map->point[i].y = current->y - param->map->point[i].alt/10 * sin(param->b);	
		param->map->point[i].x = (current->x - current->y) * cos(param->b);
		param->map->point[i].y = (current->y - param->map->point[i].alt * param->zoom) * sin(param->b) +
		   	current->x * sin(param->b);
		if (param->d_departx == 0 && param->d_departy == 0)
		{
			param->d_departx = (param->departx - param->map->point[i].x);
			param->d_departy = (param->departy - param->map->point[i].y);
		}
		param->map->point[i].x += param->d_departx;
	 	param->map->point[i].y += param->d_departy;
		//param->map->point[i].x -= (param->map->point[i].y - param->centre.y) * cos(param->rot);
		//param->map->point[i].y -= (param->map->point[i].x - param->centre.x) * sin(param->rot);
		ft_fix_color(param->map->point + i, param);
		current->x += param->ecart;
	}
	current->x = param->departx;
	current->y += param->ecart;
}

void        ft_rotate(t_param *param)
{
	t_line		*begin_lst;
	int			i;
//	int			distance_c;

	begin_lst = param->map;
	while (param->map)
	{
		i = -1;
		while (++i < param->map->size)
		{
			if (!param->map->distance[i].x && param->map->distance[i].x != param->centre.x)
			{
				param->map->distance[i].y = param->centre.y - param->map->point[i].y;
				param->map->distance[i].x = param->centre.x - param->map->point[i].x;
			}
			//distance = sqrt(pow(param->centre.y - param->map->point[i].y, 2) + pow(param->centre.x - param->map->point[i].x, 2)); 
			param->map->point[i].y = param->map->point[i].y - param->map->distance[i].x * cos(param->rot);
			param->map->point[i].x = param->map->point[i].x - param->map->distance[i].y * sin(param->rot);
			//printf("distance par rapport au centre %d\n", distance);
		}
		param->map = param->map->next;
	}
	param->map = begin_lst;
}

void        calcul_point(t_param *param, float *zoom)
{
	t_coord     current;
	t_line		*begin_lst;

	begin_lst = param->map;
	current.x = param->departx;
	current.y = param->departy;
	param->d_departx = 0;
	param->d_departy = 0;
	while (param->map)
	{
		set_point(&current, param);
		param->map = param->map->next;
	}
	calcul_centre(param);
	param->map = begin_lst;
//	ft_rotate(param);
}
