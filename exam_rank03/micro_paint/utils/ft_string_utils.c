/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:08:09 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/08 14:20:08 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_micro_paint.h"

/// This function checks if the string is a valid number or not
/// Returns 1 if an error was found or 0 if the string is a valid number
/// Possible errors:
/// 1) Characters other than "-0123456789"
/// 2) Multiple '-' in the string
/// 3) The string = '-'
int	ft_wrong_number_str(char *str)
{
	int	n_minus;
	int	i;

	i = -1;
	n_minus = 0;
	if (str[0] == '-' && !str[1])
		return (1);
	while (str[++i])
	{
		if (str[i] == '-')
			n_minus++;
		if (n_minus > 1 || str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

/// Transforms str to an int
int	ft_atoi(char *str)
{
	int	n;
	int	sign;
	int	i;

	i = -1;
	n = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[++i])
	{
		n = n * 10 + str[i] - '0';
	}
	return (sign * n);
}
