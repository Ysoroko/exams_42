/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 13:07:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/31 13:07:49 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putendl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
	ft_putchar('\n');
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_fill_string_with_backslash_zeroes(char *str, int number_of_zeroes)
{
	int	i;

	i = -1;
	while (++i <= number_of_zeroes)
		str[i] = 0;
}

int	ft_strchr(char *str, char c)
{
	int	i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	ft_union(char *str_a, char *str_b)
{
	int		i;
	int		j;
	int		k;
	char	ret_str[ft_strlen(str_a) + ft_strlen(str_b) + 1];
	int		len;

	i = -1;
	j = -1;
	k = -1;
	len = ft_strlen(str_a) + ft_strlen(str_b) + 1;
	ft_fill_string_with_backslash_zeroes(ret_str, len);
	while (str_a[++i])
	{
		if (!ft_strchr(ret_str, str_a[i]))
			ret_str[++k] = str_a[i];
	}
	while (str_b[++j])
	{
		if (!ft_strchr(ret_str, str_b[j]))
			ret_str[++k] = str_b[j];
	}
	ret_str[++k] = 0;
	ft_putendl(ret_str);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putchar('\n');
		return (-1);
	}
	ft_union(argv[1], argv[2]);
	return (0);
}