/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:27:35 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/22 15:17:20 by ysoroko          ###   ########.fr       */
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

t_command	*ft_new_t_command(int type, char **args, t_command *first)
{
	t_command	*ret;
	t_command	*temp;

	ret = malloc(sizeof(t_command));
	if (!ret)
		exit(EXIT_FAILURE);
	ret->type = type;
	ret->args = args;
	if (!first)
	{
		ret->prev = NULL;
		ret->next = NULL;
	}
	else
	{
		temp = first;
		while (temp->next);
			temp = temp->next;
		ret->prev = temp;
		ret->next = NULL;
		temp->next = ret;
	}
	return (ret);
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

void	ft_puterr(char *msg, char *file)
{
	if (!file)
		ft_putendl_fd(msg, STDERR);
	else
	{
		ft_putstr_fd(msg, STDERR);
		ft_putendl_fd(file, STDERR);
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
	
	exit(EXIT_SUCCESS);
	return (0);
}
