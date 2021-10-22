/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:27:35 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/22 14:43:58 by ysoroko          ###   ########.fr       */
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


typedef	struct s_command
{

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
	(void)argc;
	if (execve(argv[0], argv, env) == -1)
		ft_puterr(EXECVE_ERROR, argv[0]);
	exit(EXIT_SUCCESS);
	return (0);
}
