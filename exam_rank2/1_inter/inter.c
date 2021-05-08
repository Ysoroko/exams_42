/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:59:21 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/08 15:59:21 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** static int	ft_strlen(char *str)
** Calculates the length of str string
** Does not include the '\0' character in the count
*/

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
** static void	ft_fill_n_chars_with_backslash_n(char *str, int len)
** This function will fill len first character of str string with '\0' char
** Same as calloc function, but this one is used with a string on the stack
*/

static void	ft_fill_n_chars_with_backslash_n(char *str, int len)
{
	int	i;

	i = -1;
	while(++i < len)
		str[i] = 0;
}

/*
** int	ft_char_is_in_str(char *str, char c)
** This function is the same as strchr, but returns an int instead
** of the char's position (since we don't need the address of the char here)
** Returns 1 if the argument character c is present in argument str
** Returns 0 if c isn't present in str
*/

int	ft_char_is_in_str(char *str, char c)
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

/*
** void	ft_putchar(char c)
** Writes the character c on standard output
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
** void	ft_putstr_endl(char *str)
** Writes the string str on the standard input followed by a '\n'
** newline character
*/

void	ft_putstr_endl(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
	ft_putchar('\n');
}

/*
** void	ft_inter(char *a, char *b)
** This function creates and displays the string which contains all the
** characters present in both argument "a" and argument "b".
** The display is done on standard output (file descriptor 1)
** If a character is present multiple times in one/both string(s), it only
** displays it once.
** The display is followed by a '\n' newline character
*/

void	ft_inter(char *a, char *b)
{
	char	temp[ft_strlen(a) + 1];
	int		i;
	int		j;

	i = -1;
	j = -1;
	ft_fill_n_chars_with_backslash_n(temp, (ft_strlen(a) + 1));
	while (a[++i])
	{
		if (ft_char_is_in_str(b, a[i]) && !ft_char_is_in_str(temp, a[i]))
			temp[++j] = a[i];
	}
	ft_putstr_endl(temp);
}

/*
** int	main(int argc, char **argv)
** Checks the number of arguments and calls the ft_inter function
** If there isn't 2 arguments, only displays a '\n' newline on standard output
*/

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putchar('\n');
		return (1);
	}
	ft_inter(argv[1], argv[2]);
	return (0);
}