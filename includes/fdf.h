/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:44:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/03 03:31:38 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
//# define ECART 6 /*ecart calculer*/
# define W_SIZEX 2550
# define W_SIZEY 1320
# define DEPARTX W_SIZEX / 2
# define DEPARTY 300

# include "../libft/includes/libft.h"
# include "Keycode.h"

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
}						t_coord;

typedef struct	s_line
{
	char			**tab;
	int				size;
	t_coord			*point;
	t_coord			*distance;
	struct s_line	*next;
}					t_line;

typedef struct	s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_window;

typedef struct	s_param
{
	t_line			*map;
	t_line			*l_centre;
	t_window		window;
	t_coord			centre;
	
	unsigned int	ecart;
	int				max;
	float			zoom;
	double			b;
	double			rot;
	double			roty;
	int				d_departx;
	int				d_departy;
	int				departx;
	int				departy;
	int				max_color;
	int				min_color;
	int				gnd_color;
	int				n_mid_color;
	int				p_mid_color;
	int				lst_size;
}					t_param;

typedef struct	s_var_draw
{
	int		dx;
	int		dy;
	int		xincr;
	int		yincr;
	int		erreur;
	int		e;
}			t_var_draw;

typedef	struct	s_image
{
	void		*img;
	int			*data;
	int			size;
	int			bpp;
	int			a;
}				t_image;

typedef struct	s_all
{
	t_param		tt;
	t_image		image;
	t_window	wdw;
	int				press;
	int				last_x;
	int				last_y;
}				t_all;

void		calcul_centre(t_param *param);
int			get_next_line(const int fd, char **line);
int			deal_key(int key, void *param);
int			deal_mouse(int button, int x, int y, void *param);
int         release_btn(int button, int x, int y, void *param);
void		draw_line(t_coord point1, t_coord point2, t_all all ,int ecart);
void		draw_sqrt(t_all all);
//char		**ft_read_fdf(int fd);
int			ft_read_fdf(int fd, t_param *param);
void		init_point(t_coord *point);
void		calcul_point(t_param *param, float *zoom);
int         deal_mouse2(int x, int y, void *param);
void		set_point(t_coord *current, t_param *param);
t_param		init_map(t_window window, int fd);
void		ft_color(t_line *lst_map);
int			ft_select_increment(t_coord	point);
void		ft_fix_color(t_coord *point, t_param *param); // bon
//int			ft_fix_color(t_coord point); // mauvais
void		calcul_zoom(t_param *param, int lst_size);
void        ft_draw_square(t_coord point, int size, int color,t_all *all);

#endif
