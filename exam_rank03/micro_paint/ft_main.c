/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:22:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/07 11:36:52 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_micro_paint.h"

static int	ft_analyze_args_and_init_file(int argc, char **argv, FILE **file)
{
	if (argc != 2)
	{
		ft_putendl_fd(WRONG_N_ARGS, STDOUT);
		return (1);
	}
	if (!fopen(argv[1], "r"))
	{
		ft_putendl_fd(CORRUPTED_FILE, STDOUT);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*file;

	if (ft_analyze_args_and_init_file(argc, argv, &file))
		return (1);

	return (0);
}
