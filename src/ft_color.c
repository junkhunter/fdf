/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:08:52 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/20 15:28:30 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <math.h>
#include <mlx.h>
#include "../includes/fdf.h"
# define limit 255

int		ft_select_increment(t_coord	point)
{
	if (point.alt < -limit)
		return (0X000001);
	else if (point.alt < 0)
		return (0X000100);
	else if (point.alt < limit / 2)
		return (0X000002);
	else if (point.alt < limit)
		return (0X010000);
	else if (point.alt < limit * 2)
		return (-0X000100);
	return (0);
}	

int		ft_fix_color(t_coord point)
{
	int inc;

	inc = ft_select_increment(point);
	if (point.alt < -limit)
		return ((abs(point.alt + limit) * inc > 0X000050) ? 
			abs(point.alt + limit) * inc : 0x00000D0);
	else if (point.alt < 0)
		return (0X0000FF + (point.alt + limit) * inc);
	else if (point.alt < limit/2)
		return (0X00FFFF - point.alt * inc);
	else if (point.alt < limit)
		return (0X00FF00 + (point.alt) * inc);
	else if (point.alt < limit * 2)
		return (0XFF0000 + (point.alt - limit) * inc);
	return (0XFFFFFF);
}
