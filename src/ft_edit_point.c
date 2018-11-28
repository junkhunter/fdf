/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 01:51:30 by rhunders          #+#    #+#             */
/*   Updated: 2018/11/28 17:00:35 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include <math.h>
# define DEPARTY -400
# define DEPARTX 700

#define limit 255

void        init_point(t_coord *point)
{
	point->x =DEPARTX;
	point->y = DEPARTY;
}

void		set_point(t_coord *current, t_param param)
{
	int i;

	i = -1;
	while (++i < param.map->size)
	{
		param.map->point[i].alt *= param.zoom;
		//if (map->point[i].alt < 0)
		//	map->point[i].alt = 0;
		param.map->point[i].x = (current->x - current->y) * cos(0.5);
		param.map->point[i].y = (current->y - (param.map->point[i].alt /** param.zoom*/) + current->x) * sin(0.5);
		param.map->point[i].color = ft_fix_color(param.map->point[i]);
		current->x += param.ecart;
	}
	current->x = DEPARTX;
	current->y += param.ecart;
}

void        calcul_point(t_param param, int ecart, float *zoom)
{
	t_coord     current;

	param.ecart = ecart;
	*zoom = calcul_zoom(param.map);
	param.zoom = *zoom;
	init_point(&current);
	while (param.map)
	{
		param.zoom = *zoom;
		set_point(&current, param);
		param.map = param.map->next;
	}
}
