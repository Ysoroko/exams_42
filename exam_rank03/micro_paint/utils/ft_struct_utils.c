/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:20:24 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/08 17:23:26 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_micro_paint.h"

void	*ft_calloc(size_t size)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	while (i < size)
	{
		ret[i] = 0;
		i++;
	}
	return (ret);
}
