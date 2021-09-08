/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_micro_paint.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:26:24 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/08 15:26:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MICRO_PAINT_H
# define FT_MICRO_PAINT_H

# include <stdio.h>
# include <unistd.h>

/*
** PRINT_UTILS.C
*/

void	ft_putendl_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);

/*
** FT_STRING_UTILS.C
*/

int		ft_strchr(char *str, char c);


# define WRONG_N_ARGS "Error: argument"
# define CORRUPTED_FILE "Error: Operation file corrupted"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

#endif