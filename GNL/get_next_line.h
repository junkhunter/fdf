/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:31 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/02 21:43:01 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1500
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>

int		get_next_line(const int fd, char **line);

#endif
