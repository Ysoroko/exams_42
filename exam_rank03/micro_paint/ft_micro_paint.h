/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_micro_paint.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:26:24 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/07 11:29:51 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MICRO_PAINT_H
# define FT_MICRO_PAINT_H

# include <stdio.h>
# include <unistd.h>

void	ft_putendl_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);

# define WRONG_N_ARGS "Error: argument"
# define CORRUPTED_FILE "Error: Operation file corrupted"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

#endif