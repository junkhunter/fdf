/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 01:51:30 by rhunders          #+#    #+#             */
/*   Updated: 2018/11/29 14:35:48 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fdf.h"
#include <math.h>
# define DEPARTY 300
# define DEPARTX 1200

#define limit 255

void        init_point(t_coord *point)
{
	point->x = DEPARTX;
	point->y = DEPARTY;
}

void		set_point(t_coord *current, t_param param)
{
	int i;
	i = -1;

	while (++i < param.map->size)
	{
		param.map->point[i].alt = ft_atoi(param.map->tab[i]) * param.zoom;
		param.map->point[i].x = ((current->x /*- (param.map->point[i].alt / 10)*/) * cos(param.b)) - 
			(((current->y - DEPARTY)) * cos(param.rot));
		param.map->point[i].y = (current->y - (param.map->point[i].alt)) * sin(param.b) + 
			((current->x - DEPARTX)) * sin(param.rot);
		param.map->point[i].color = ft_fix_color(param.map->point[i]);
		current->x += param.ecart;
	}
	current->x = param.departx;
	current->y += param.ecart;
}

void        calcul_point(t_param param, int ecart, float *zoom)
{
	t_coord     current;
	t_line		*begin_lst;

	begin_lst = param.map;
	param.ecart = ecart;
	param.departx = DEPARTX;/*(DEPARTX * cos(param.b) - (DEPARTY * cos(param.rot))) +
	*/ //  	(DEPARTX - (DEPARTX * cos(param.b) - (DEPARTY * cos(param.rot))));
	current.x = DEPARTX;
	current.y = DEPARTY
		/* ((DEPARTY - (param.map->point->alt)) * sin(param.b) + DEPARTX * sin(param.rot)) +
	   	(DEPARTY  - ((DEPARTY - (param.map->point->alt)) * sin(param.b) + DEPARTX * sin(param.rot)))*/;
	//printf("depart y -> %d\ndepart x -> %d\n", current.y, current.x);
	while (param.map)
	{
		set_point(&current, param);
		param.map = param.map->next;
	}
	printf("depart y -> %d\ndepart x -> %d\n", begin_lst->point->y, begin_lst->point->x);
	printf("depart line %d\n", (begin_lst->point->y - 100) * W_SIZEX + begin_lst->point->x);
	param.departx = begin_lst->point->x;
	//param.departy = begin_lst->point->y;
}
