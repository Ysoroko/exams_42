/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:22:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/08 17:44:33 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_micro_paint.h"

static int	ft_analyze_args_and_init_file(int argc, char **argv, FILE **file)
{
	FILE	*f;
	if (argc != 2)
	{
		ft_putendl_fd(WRONG_N_ARGS, STDOUT);
		return (1);
	}
	f = fopen(argv[1], "r");
	if (!f)
	{
		ft_putendl_fd(CORRUPTED_FILE, STDOUT);
		return (1);
	}
	*file = f;
	return (0);
}

static t_first_line *ft_init_first_line(FILE *file)
{
	int				width;
	int				height;
	char			fill_char;
	char			too_much_args;
	t_first_line	*ret;

	fscanf(file, "%d %d %c %c ", &width, &height, &fill_char, &too_much_args);
	if (too_much_args)
		return (NULL);
	ret = ft_calloc(sizeof(t_first_line));
	if (!ret)
		return (NULL);
	ret->screen_width = width;
	ret->scren_height = height;
	ret->background_char = fill_char;
	return (ret);
}

int	main(int argc, char **argv)
{
	FILE			*file;
	t_first_line	*f_line;

	if (ft_analyze_args_and_init_file(argc, argv, &file))
		return (1);
	f_line = ft_init_first_line(file);
	if (!f_line)
	{
		ft_putendl_fd(CORRUPTED_FILE, STDOUT);
		return (1);
	}
	return (0);
}
