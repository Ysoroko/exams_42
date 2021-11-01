/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:27:35 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/01 14:56:09 by ysoroko          ###   ########.fr       */
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
	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (NULL);
	while (str[++i])
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

static char **ft_copy_str_tab(char **tab, int n_elements)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc(sizeof(char *) * (n_elements + 1));
	if (!ret)
		return (NULL);
	while (tab[++i] && i < n_elements)
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
			return (NULL);
	}
	ret[i] = NULL;
	return (ret);
}

/// 1) Find a '|' or a ';'
/// 2) Extract everything until then as a t_command
void	ft_parse_user_input(t_command *cmd, char **argv)
{
	int			i;
	t_command	*temp;

	i = -1;
	while (argv[++i])
	{
		
	}
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
	ft_parse_user_input(&cmd, &(argv[1]));
	if (execve(argv[1], argv, env) == -1)
		printf("Error\n");
	else
	{
		printf("OK\n");
	}
	return (0);
}
