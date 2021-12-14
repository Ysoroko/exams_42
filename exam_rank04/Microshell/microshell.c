/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/12/14 17:37:14 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// ------------------------- MACROS ANS STRUCTURES ----------------------------

typedef struct	s_cmd
{
	int				fd[2];
	char			**tab;
	char			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define CD_N_ARGS_ERR "error: cd: bad arguments"
#define CD_ERR "error: cd: cannot change directory to " //path to add!

#define SYS_ERR "error: fatal"
#define EXECVE_ERR "error: cannot execute " //executable to add!

#define EXIT 1
#define NO_EXIT 0

// ----------------------------- DEBUG --------------------------------------

void	ft_print_str_tab(char **tab)
{
	int i = -1;
	int	j = 0;

	printf("\n\n ----------- TAB ----------- \n\n");
	while (tab[++i])
	{
		printf("[%d]:\t%s\n", ++j, tab[i]);
	}
	printf("\n\n --------------------------- ");
}

void	ft_print_cmd_list(t_cmd	*first)
{
	int		i = 0;
	t_cmd	*temp = first;

	while (temp)
	{
		printf("\n\n\n----------------------- [%d] -----------------------\n\n", ++i);
		printf("TYPE: [%c]\n", temp->type);
		ft_print_str_tab(temp->tab);
		temp = temp->next;
	}
	printf("\n\n\n----------------------------------------------------");
}

// ------------------------------ UTILS -------------------------------------

int	ft_strlen(char *str)
{
	int i = 0;
	
	if(!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_puterr(char *msg, char *arg, int to_exit)
{
	ft_putstr_fd(msg, STDERR);
	if (arg)
		ft_putstr_fd(arg, STDERR);
	ft_putchar_fd('\n', STDERR);
	if (to_exit)
		exit(EXIT_FAILURE);
}

// ----------------------------- T_CMD UTILS ----------------------

t_cmd	*ft_new_t_cmd(char **tab, char type)
{
	t_cmd	*ret = malloc(sizeof(t_cmd));

	if (!ret)
		ft_puterr(SYS_ERR, NULL, EXIT);
	ret->tab = tab;
	ret->type = type;
	ret->prev = NULL;
	ret->next = NULL;
	return (ret);
}

void	ft_cmd_add_back(t_cmd **start, t_cmd *next)
{
	t_cmd	*temp = *start;

	if (!*start)
		*start = next;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = next;
		next->prev = temp;
	}
}

// ----------------------------- PARSING --------------------------

char	ft_get_type(char *str)
{
	if (!strcmp(str, ";"))
		return (';');
	if (!strcmp(str, "|"))
		return ('|');
	return (0);
}

t_cmd	*ft_parse_args(char **argv)
{
	t_cmd	*ret = NULL;
	char	**start = argv;
	int		i = -1;
	t_cmd	*temp = NULL;
	char	type = 0;

	while (argv[++i])
	{
		type = ft_get_type(argv[i]);
		if (type)
		{
			temp = ft_new_t_cmd(start, type);
			ft_cmd_add_back(&ret, temp);
			argv[i] = NULL;
			start = &(argv[i + 1]);
		}
	}
	temp = ft_new_t_cmd(start, type);
	ft_cmd_add_back(&ret, temp);
	return (ret);
}


// ----------------------------- MAIN --------------------------

int	main(int argc, char **argv)
{
	t_cmd	*lst;
	
	if (argc == 1)
		return (0);
	lst = ft_parse_args(&(argv[1]));
	ft_print_cmd_list(lst);
	return (0);
}
