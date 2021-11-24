/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/24 10:45:24 by ysoroko          ###   ########.fr       */
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
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			**tab_for_execve;
	char			type;
}	t_cmd;

// Error messages
#define CD_ARG_ERR "error: cd: bad arguments"
#define CD_FAIL_ERR "error: cd: cannot change directory to " //followed by path
#define SYS_ERR "error: fatal"
#define EXECVE_ERR "error: cannot execute " //followed by the exe name!

// Error output file descriptor
#define STDERR 2

// Macros which determine if we exit in ft_puterr
#define EXIT 1
#define NO_EXIT 0

#define PIPE '|'
#define SEP ';'
#define STD '0'

// ---------------------------- Debug ----------------------------------------

void	ft_print_str_tab(char **tab)
{
	int	i;

	i = -1;
	printf("STR_TAB:\n");
	printf("-----------------\n");
	while (tab[++i])
		printf("%s\n", tab[i]);
	printf("-----------------\n");
}

void	ft_print_cmd_list(t_cmd *first)
{
	t_cmd	*temp;
	int		i;

	temp = first;
	i = 1;
	while (temp)
	{
		printf("%d\n", i);
		ft_print_str_tab(temp->tab_for_execve);
		printf("Type: [%c]\n", temp->type);
		printf("-----------------\n");
		temp = temp->next;
		i++;
	}
}

// ------------------------------ Utils --------------------------------------

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
	ft_putchar_fd('\n', 2);
	if (to_exit)
		exit(EXIT_FAILURE);
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
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

// ---------------------------- t_cmd utils ----------------------------------

t_cmd	*ft_new_t_cmd_exit(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_puterr(SYS_ERR, NULL, EXIT);
	cmd->tab_for_execve = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->type = '0';
	return (cmd);
}

void ft_cmd_add_back(t_cmd **first, t_cmd *to_add)
{
	t_cmd	*last;
	
	if (!to_add)
		return ;
	if (!*first)
	{
		*first = to_add;
		return ;
	}
	last = *first;
	while (last->next)
		last = last->next;
	last->next = to_add;
	to_add->prev = last;
}

// ------------------------------ Parsing ------------------------------------

/*
** Calculates the length needed to malloc a tab of strings until ";" or "|"
*/

int	ft_str_tab_len_needed(char **argv)
{
	int		i;

	if (!argv)
		return (0);
	i = -1;
	while (argv[++i])
	{
		if (ft_pipe_or_sep(argv[i]))
			return (i + 1);
	}
	return (i);
}

char	ft_pipe_or_sep(char *str)
{
	if (!strcmp(str, "|"))
		return ('|');
	if (!strcmp(str, ";"))
		return (';');
	return (0);
}

/*
** Creates an array of strings composed of n_elems_to_copy next elements of src
*/

char	**ft_strtab_n_copy_exit(char **src, int n_elems_to_copy)
{
	int		i;
	char	**ret;

	ret = malloc(sizeof(*ret) * (n_elems_to_copy + 2));
	if (!ret)
		ft_puterr(SYS_ERR, NULL, EXIT);
	i = -1;
	while (src[++i] && i < n_elems_to_copy)
	{
		ret[i] = ft_strdup_exit(src[i]);
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_extract_and_add_command(t_cmd **first, char **checkpnt, int i, int *j)
{
	t_cmd	*temp;
	char	**tab_for_execve;
	int		len;


	temp = ft_new_t_cmd_exit();
	len = ft_str_tab_len_needed(checkpnt);
	tab_for_execve = ft_strtab_n_copy_exit(checkpnt, len);
	temp->tab_for_execve = tab_for_execve;
	temp->type = ft_pipe_or_sep(checkpnt[len - 1]);
	ft_cmd_add_back(first, temp);
	*j = i + 1;
}

// ------------------------------ Main ------------------------------------

t_cmd	*ft_extract_command_list(char **argv)
{
	t_cmd	*ret;
	int		i;
	int		j;

	i = 0;
	ret = NULL;
	j = 1;
	while (argv[++i])
	{
		if (ft_pipe_or_sep(argv[i]))
			ft_extract_and_add_command(&ret, &(argv[j]), i, &j);
	}
	ft_extract_and_add_command(&ret, &(argv[j]), i, &j);
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*lst;

	int i = 0;
	while (argv[++i])
		printf("argv[%d]: %s\n", i, argv[i]);
	lst = ft_extract_command_list(argv);
	ft_print_cmd_list(lst);
	return (0);
}
