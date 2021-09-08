/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:22:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/08 15:36:51 by ysoroko          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	FILE	*file;

	if (ft_analyze_args_and_init_file(argc, argv, &file))
		return (1);
	int i, f;
	char ch;

	printf("%d %d %c \n", i, f, ch);
	return (0);
}
