/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 23:07:37 by rhunders          #+#    #+#             */
/*   Updated: 2018/12/03 03:12:40 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

#include <time.h>
int     ft_strsplit_v2(char const *s, char c, char ***new);

int		ft_read_fdf(int fd, t_param *param)
{
	char	*line;
	char	**tab;
	clock_t	time = clock();

	if (get_next_line(fd, &line) > 0) //si erreur de read???
	{
	//	printf("duree de GNL -> %Lf sec\n", (((long double)clock() - (long double)time) / (long double)CLOCKS_PER_SEC));
		//time = clock();
		param->map->size = ft_strsplit_v2(line, ' ', &param->map->tab);
		//printf("duree de split -> %Lf sec\n", (((long double)clock() - (long double)time) / (long double)CLOCKS_PER_SEC));
		free(line);
		return (1);
	}
	return (0);
}

#include <stdio.h>

void	calcul_zoom(t_param *param, int lst_size)
{
	int		i;
	t_line *lst_map;
	int		i2;

	param->max = 1;
	lst_map = param->map;
	i2 = 0;
	while (lst_map && ++i2)
	{
		i = -1;
		while (++i < lst_map->size)
		{
			lst_map->point[i].alt = ft_atoi(lst_map->tab[i]);
			if (abs(lst_map->point[i].alt) >= param->max)
				param->max = abs(lst_map->point[i].alt);
			if (lst_size && i2 == lst_size && i2++)
				param->l_centre = lst_map;
		}
		lst_map = lst_map->next;
	}
	param->zoom = (param->max < 150.0) ? 150.0 / param->max: 1;
}

void	calcul_centre(t_param *param)
{
	param->centre = param->l_centre->point[param->l_centre->size/2];
}

# define SIZE_MINX (W_SIZEX - W_SIZEX / 100)
# define SIZE_MINY (W_SIZEY - W_SIZEY / 100)

t_param	init_map(t_window window, int fd)
{
	t_param		param;	
	t_line		*begin_lst;
	t_line		*tmp;

	if (!(param.map = (t_line*)malloc(sizeof(t_line))) || (param.lst_size = 0))
		return (param);
	begin_lst = param.map;
	param.ecart = 100;
	param.b = 0.5;
	param.rot = 18.35;
	
	param.max_color = RED;
	param.min_color = ELECTRIC_ULTRAMARINE;
	param.gnd_color = CYAN;
	param.n_mid_color = PURPLE;
	param.p_mid_color = ORANGE;
	
	param.departx = DEPARTX;
	param.departy = DEPARTY;
	clock_t time = clock();
	while ((ft_read_fdf(fd, &param)))
	{
		//printf("duree de read_fdf -> %Lf sec\n", (((long double)clock() - (long double)time) / (long double)CLOCKS_PER_SEC));
		if (param.ecart * param.map->size > SIZE_MINY && param.ecart * param.map->size > SIZE_MINX)
			param.ecart = ((SIZE_MINY < SIZE_MINX) ? SIZE_MINX : SIZE_MINY) / (param.map->size + 1);
		param.map->point = (t_coord*)malloc(sizeof(t_coord) * param.map->size);
		//param.map->distance = (t_coord*)malloc(sizeof(t_coord) * param.map->size);
		//ft_memset(param.map->distance, 0, sizeof(t_coord) * param.map->size);
		
		param.map->next = (t_line*)malloc(sizeof(t_line));
		tmp = param.map;
		param.map = param.map->next;
		param.lst_size++;
	}
	printf("duree de read -> %lf sec\n", (((double)clock() - (double)time) / (double)CLOCKS_PER_SEC));
	free(param.map);
	tmp->next = NULL;
	param.map = begin_lst;
	calcul_zoom(&param, param.lst_size / 2);
	if (param.ecart > 1)
		param.ecart /= 2;
	else
		param.ecart = 1;
	calcul_point(&param, &param.zoom);
	return (param);
}
