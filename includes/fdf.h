/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:44:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/17 19:40:51 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define ECART 6
# define W_SIZEX 2550
# define W_SIZEY 1320
# include "../libft/includes/libft.h"

/*couleur de base*/
# define RED    0XFF0000
# define GREEN  0X00FF00
# define BLUE   0X0000FF
# define YELLOW 0XFFFF00
# define PURPLE 0XFF00FF
# define CYAN   0X00FFFF
# define BLACK  0X000000
# define WHITE  0XFFFFFF

/*couleur bonus*/
# define DARK_BROWN 0X654321
# define ELECTRIC_BLUE 0X7DF9FF
# define GRAY 0X808080
# define HEART_GOLD 0X808000
# define LAVENDER_BLUE 0XCCCCFF
# define ELECTRIC_ULTRAMARINE 0X3F00FF
# define EGGPLANT 0X614051
# define DOLLAR_BILL 0X85BB65
# define OLIVE 0XBAB86C
# define ORANGE 0XFFA500
# define PINE_GREEN 0X01796F

#include <fcntl.h>
#include "../GNL/get_next_line.h"
#include <mlx.h>

typedef struct	s_coord
{
	int					x;
	int					y;
	int					alt;
	unsigned int		color;
}				t_coord;

typedef struct	s_line
{
	char			**tab;
	int				size;
	t_coord			*point;
	struct s_line	*next;
	double			b;
	unsigned int	ecart;
	unsigned int	zoom;
}				t_line;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_window;

typedef struct	s_var_draw
{
	int     dx;
	int     dy;
	int     xincr;
	int     yincr;
	int     erreur;
	int     e;
}				t_var_draw;

int			get_next_line(const int fd, char **line);
int			deal_key(int key, void *param);
void		draw_line(t_coord point1, t_coord point2, t_window window/*, int color*/);
void		draw_sqrt(t_window window, t_line *lst_map);
char		**ft_read_fdf(int fd);
void		init_point(t_coord *point);
t_line		*init_map(t_window window, int fd);
void		ft_color(t_line *lst_map);

#endif
