/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 23:07:37 by rhunders          #+#    #+#             */
/*   Updated: 2018/11/29 14:43:32 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

char		**ft_read_fdf(int fd)
{
	char	*line;
	char	**tab;

	if (get_next_line(fd, &line) > 0) //si erreur de read???
	{
		tab = ft_strsplit(line, ' ');
		free (line);
		return (tab);
	}
	return (NULL);
}

#include <stdio.h>

float	calcul_zoom(t_line *lst_map)
{
	int i;
	int max;
	float zoom;

	i = -1;
	max = 1;
	while (lst_map)
	{
		i = -1;
		while (++i < lst_map->size)
		{
			lst_map->point[i].alt = ft_atoi(lst_map->tab[i]);
			if (abs(lst_map->point[i].alt) >= max)
				max = abs(lst_map->point[i].alt);
		}
		lst_map = lst_map->next;
	}
	zoom = 150 / max;
	if (zoom < 1)
		zoom = 1;
	return (zoom);
}

# define SIZE_MINX (W_SIZEX - W_SIZEX/100)
# define SIZE_MINY (W_SIZEY - W_SIZEY/100)

t_coord		set_centre(t_line *lst, int size)
{
	//t_line *lst;

	//lst = tt->map;
	while (size--)	
		lst = lst->next;
	return (lst->point[lst->size / 2]);
}

t_param		init_map(t_window window, int fd)
{
	t_param		param;	
	t_line		*begin_lst;
	t_line		*tmp;
	int			i;

	if (!(param.map = (t_line*)malloc(sizeof(t_line))) || (i = 0))
		return (param);
	begin_lst = param.map;
	param.ecart = 100;
	param.b = 0.5;
	param.rot = 0.5;
	while ((param.map->tab = ft_read_fdf(fd)))
	{
		param.map->size = 0;
		while (param.map->tab[param.map->size]) //taille de la ligne
			param.map->size++;
		if (param.ecart * param.map->size > SIZE_MINY &&
			 param.ecart * param.map->size > SIZE_MINX)
			param.ecart = ((SIZE_MINY < SIZE_MINX) ? SIZE_MINX : SIZE_MINY) / (param.map->size + 1);
		param.map->point = (t_coord*)malloc(sizeof(t_coord) * param.map->size);
		param.map->next = (t_line*)malloc(sizeof(t_line));
		tmp = param.map;
		param.map = param.map->next;
		i++;
	}
	free(param.map);
	tmp->next = NULL;
	param.map = begin_lst;
	if (i > 0)
		param.centre = set_centre(begin_lst, i / 2);
	param.zoom = calcul_zoom(param.map);
	calcul_point(param, param.ecart / 2, &param.zoom);
	return (param);
}
