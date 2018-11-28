/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 23:07:37 by rhunders          #+#    #+#             */
/*   Updated: 2018/11/28 16:01:29 by rhunders         ###   ########.fr       */
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

t_line		*init_map(t_window window, int fd, float *zoom)
{
	t_line		*lst_map;
	t_line		*begin_lst;
	t_line		*tmp;
	int			ecart;

	lst_map = (t_line*)malloc(sizeof(t_line));
	begin_lst = lst_map;
	ecart = 100;
	//lst_map->zoom = *zoom;
	//*zoom = 6;
	while ((lst_map->tab = ft_read_fdf(fd)))
	{
		lst_map->size = 0;
		while (lst_map->tab[lst_map->size]) //taille de la ligne
			lst_map->size++;
		if (ecart * lst_map->size > SIZE_MINY &&
			 ecart * lst_map->size > SIZE_MINX)
			ecart = ((SIZE_MINY < SIZE_MINX) ? SIZE_MINX : SIZE_MINY) / (lst_map->size + 1);
		lst_map->point = (t_coord*)malloc(sizeof(t_coord) * lst_map->size);
		lst_map->next = (t_line*)malloc(sizeof(t_line));
		tmp = lst_map;
		lst_map = lst_map->next;
	}
	free(lst_map);
	tmp->next = NULL;
	calcul_point(begin_lst, ecart / 2, zoom);
	printf("coucou\n");
	return (begin_lst);
}
