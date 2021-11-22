/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/22 10:50:07 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
** Macros and structures:
** ----------------------------------------------------------------------------
*/

typedef struct s_cmd
{
	t_cmd	*next;
	t_cmd	*prev;
	char	**args;
	int		type;
}	t_cmd;

#define CD_ARG_ERR "error: cd: bad arguments"
#define CD_FAIL_ERR "error: cd: cannot change directory to " //followed by path
#define SYS_ERR "error: fatal"
#define EXECVE_ERR "error: cannot execute " //followed by the exe name!

#define STDERR 2
#define EXIT 1
#define NO_EXIT 0

/*
** Utils:
** ----------------------------------------------------------------------------
*/

int	ft_strlen(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_puterr(char *str, char *str2, int to_exit)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		ft_putchar_fd(str[i], 2);
	if (str2)
	{
		i = -1;
		while (str2[++i])
			ft_putchar_fd(str[i], 2);
	}
	ft_putchar('\n', 2);
	if (to_exit)
		exit(EXIT_FAILURE);
}

/*
** Calculates the length needed to malloc a tab of strings until ";" or "|"
*/

int	ft_str_tab_len_needed(char **argv)
{
	int		i;
	char	*current_elem;

	if (!argv)
		return (0);
	i = -1;
	while (argv[++i])
	{
		current_elem = argv[i];
		if (!strcmp(current_elem, "|") || !strcmp(current_elem, ";"))
			return (i + 1);
	}
	return (i);
}

char	*ft_strdup_exit(char *str)
{
	int		i;
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		ft_puterr(SYS_ERR, NULL, EXIT);
	while (str[++i])
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

/*
** Creates an array of strings composed of n_elems_to_copy next elements of src
*/

char	**ft_strtab_n_copy(char **src, int n_elems_to_copy)
{
	int		i;
	char	**ret;

	ret = malloc(sizeof(*ret) * n_elems_to_copy + 1);
	if (!ret)
		ft_puterr(SYS_ERR, NULL, EXIT);
	i = -1;
	while (src[++i] && i < n_elems_to_copy)
		ret[i] = ft_strdup_exit(src[i]);
	ret[i] = NULL;
	return (ret);
}

/*
** Main:
** ----------------------------------------------------------------------------
*/

int	main(int argc, char **argv, char **env)
{
	
}