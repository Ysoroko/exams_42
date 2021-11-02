/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:27:35 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/02 13:31:08 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define CD_ARG_ERROR "error: cd: bad arguments"
#define CD_FAIL_ERROR "error: cd: cannot change directory to " // add the dir!
#define FATAL_ERROR "error: fatal"
#define EXECVE_ERROR "error: cannot execute " // exec to add!

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define TYPE_ONE 1
#define TYPE_PIPED 2
#define TYPE_SEPARATE 3

typedef	struct s_command
{
	int					type; //one command , piped or ';'
	int					pipes[2];
	char				**args;
	struct s_command	*prev;
	struct s_command	*next;

}	t_command;

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

static char	*ft_strdup(char *str)
{
	char	*ret;
	int		i;

	i = -1;
	if (!str)
		return(NULL);
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	while (str[++i])
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

static int	ft_strcmp(char *str1, char *str2)
{
	int	i;
	
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static t_command	*ft_new_t_command(void)
{
	t_command	*ret;

	ret = malloc(sizeof(t_command));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->args = 0;
	ret->next = 0;
	ret->prev = 0;
	ret->type = 0;
	return (ret);
}

int	ft_arg_is_a_separator(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (TYPE_PIPED);
	else if (!ft_strcmp(str, ";"))
		return (TYPE_SEPARATE);
	return (0);
}

static int	ft_needed_str_tab_len(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && !ft_arg_is_a_separator(argv[i]))
	{
		i++;
	}
	return (i);
}

static int	ft_determine_type(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
	{
		i++;
	}
	return (ft_arg_is_a_separator(str_tab[i - 1]));
}

static void	ft_add_elem_to_str_tab(char *str, char **str_tab)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str_tab[i])
		i++;
	str_tab[i] = ft_strdup(str);
}

static void	ft_add_to_list(t_command **f, t_command **t, char *str, char **str_tab)
{
	t_command	*new_elem;

	ft_add_elem_to_str_tab(str, str_tab);
	if (!*t)
	{
		(*f)->args = str_tab;
		(*f)->type = ft_determine_type(str_tab);
		*t = ft_new_t_command();
		(*t)->prev = *f;
	}
	else
	{
		(*t)->args = str_tab;
		(*t)->type = ft_determine_type(str_tab);
		new_elem = ft_new_t_command();
		new_elem->prev = *t;
		(*t)->next = new_elem;
		*t = new_elem;
	}
}

static char	**ft_initialize_str_tab_for_execve(char **argv)
{
	int		len;
	char	**ret;
	int		i;

	if (!argv[0])
		return (NULL);
	len = ft_needed_str_tab_len(argv);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	i = 0;
	while (i <= len)
	{
		ret[i] = NULL;
		i++;
	}
	return (ret);
}

static void	ft_print_str_tab(char **str_tab)
{
	int	i;

	i = -1;
	if (!str_tab)
		return ;
	while (str_tab[++i])
		printf("[%d]\t%s\n", i, str_tab[i]);
}

void	ft_print_commands(t_command *first)
{
	t_command	*temp;

	temp = first;

	while (temp)
	{
		printf("\n\n\n------------------------------\n\n\n");
		printf("Type: [%d]\n", temp->type);
		printf("Str tab for execve: \n");
		ft_print_str_tab(temp->args);
		printf("\n\n\n------------------------------\n\n\n");
		temp = temp->next;
	}
}

/// 1) Find a '|' or a ';'
/// 2) Extract everything until then as a t_command
void	ft_parse_user_input(t_command **cmd, char **argv, int argc)
{
	int			i;
	char		**str_tab_for_execve;
	t_command	*first;
	t_command	*temp;

	i = 1;
	first = ft_new_t_command();
	*cmd = first;
	temp = NULL;
	str_tab_for_execve = ft_initialize_str_tab_for_execve(argv);
	while (i < argc)
	{
		if (ft_arg_is_a_separator(argv[i]))
		{
			ft_add_to_list(cmd, &temp, argv[i], str_tab_for_execve);
			ft_initialize_str_tab_for_execve(&(argv[i + 1]));
		}
		else
		{
			ft_add_elem_to_str_tab(argv[i], str_tab_for_execve);
		}
		i++;
	}
	ft_add_to_list(&first, &temp, argv[i], str_tab_for_execve);
}

// fork() returns 0 to the child, pid of the child to the parent, -1 if error

// wait() : waits for the child process (does not specify which one)
//	argument of wait: NULL (tells what happened to the process)
//	if wait return -1 -> error -> no children to wait for (can be called in children too)
//	otherwise, wait returns the process id you waited for

// pipe(int fd[2]); -- like a file descriptor which allows to communicate between 2 processes
// pipe before fork to allow the child process to inherit the fd[2]
// fd[0] is a "read" end, fd[1] is a "write" end
int	main(int argc, char **argv, char **env)
{
	t_command	*cmd;

	if (argc == 1)
		return (0);
	(void)env;
	ft_parse_user_input(&cmd, argv, argc);
	ft_print_commands(cmd);
	return (0);
}
