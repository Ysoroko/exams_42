/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:12:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/12/15 15:28:21 by ysoroko          ###   ########.fr       */
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

int		ft_str_tab_len(char **tab)
{
	int i = 0;

	while (tab[i])
		i++;
	return (i);
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

// ---------------------------- EXECUTION --------------------------

int	ft_cd(char **tab)
{
	char	*cd_arg;

	if (ft_str_tab_len(tab) < 2)
	{
		ft_puterr(CD_N_ARGS_ERR, NULL, NO_EXIT);
		return (1);
	}
	cd_arg = tab[1];
	if (chdir(cd_arg) < 1)
	{
		ft_puterr(CD_ERR, cd_arg, NO_EXIT);
		return (1);
	}
	return (0);
}

void	ft_child_process(t_cmd *cmd, char **env)
{
	char	*exe = cmd->tab[0];
	char	**tab = cmd->tab;

	if (cmd->type == '|')
		dup2(cmd->fd[1], STDOUT);
	if (cmd->prev && cmd->prev->type == '|')
		dup2(cmd->prev->fd[0], STDIN);
	if (execve(exe, tab, env) < 0)
		ft_puterr(EXECVE_ERR, exe, EXIT);
}

int	ft_parent_process(t_cmd *cmd, int fork_ret)
{
	int	ret = 0;
	int	status;

	waitpid(fork_ret, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (cmd->type == '|' || (cmd->prev && cmd->prev->type == '|'))
	{
		close(cmd->fd[1]);
		if (cmd->type != '|')
			close(cmd->fd[0]);
	}
	if (cmd->prev && cmd->prev->type == '|')
		close(cmd->prev->fd[0]);
	return (ret);
}

int	ft_fork_and_execve(t_cmd *cmd, char **env)
{
	int	ret = 0;
	int	fork_ret = 0;

	if (cmd->type == '|' || (cmd->prev && cmd->prev->type == '|'))
		pipe(cmd->fd);
	fork_ret = fork();
	if (!fork_ret)
		ft_child_process(cmd, env);
	else
		ret = ft_parent_process(cmd, fork_ret);
	return (ret);
}

int	ft_execute_cmd(t_cmd *cmd, char **env)
{
	char	**tab = cmd->tab;
	char	*exe = NULL;
	int		ret = 0;

	if (!tab || !tab[0])
		return (0);
	exe = tab[0];
	if (!strcmp(exe, "cd"))
		ret = ft_cd(tab);
	else
		ret = ft_fork_and_execve(cmd, env);
	return (ret);
}

void	ft_execute_command_list(t_cmd *lst, char **env)
{
	t_cmd	*current = lst;
	int		ret = 0;

	while (current)
	{
		ret = ft_execute_cmd(current, env);
		current = current->next;
	}
	exit(ret);
}

// ----------------------------- MAIN ------------------------------

int	main(int argc, char **argv, char **env)
{
	t_cmd	*lst;
	
	if (argc == 1)
		return (0);
	lst = ft_parse_args(&(argv[1]));
	ft_execute_command_list(lst, env);
	return (0);
}
