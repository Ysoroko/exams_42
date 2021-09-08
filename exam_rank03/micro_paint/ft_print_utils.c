/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:23:47 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/07 11:26:00 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_micro_paint.h"

void	ft_putchar_fd(char c, int fd)
{
	write (1, &c, fd);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_putchar(str[i], fd);
}

void	ft_putendl_fd(char *str, int fd)
{
		int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_putchar(str[i], fd);
	ft_putchar('\n', fd);
}
