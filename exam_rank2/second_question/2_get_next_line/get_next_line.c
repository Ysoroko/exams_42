/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:47:59 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/18 11:36:41 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char	*str)
{
	int i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(ft_strlen(str) + 1);
	if (!ret)
		return (0);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strjoin(char *pref, char *suff)
{
	int		i;
	int		j;
	char	*ret;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(pref) + ft_strlen(suff) + 1;
	if (!pref)
		return (ft_strdup(suff));
	ret = malloc(len);
	if (!ret)
		return (0);
	while (pref[i])
	{
		ret[i] = pref[i];
		i++;
	}
	while (suff[j])
	{
		ret[i] = suff[j];
		i++;
		j++;
	}
	ret[i] = 0;
	return (ret);
}


int	get_next_line(char **line)
{
	char	buffer[2];
	char	*temp;
	int		read_ret;

	if (!line)
		return (-1);
	temp = 0;
	*line = 0;
	while ((read_ret = read(0, buffer, 1)) > 0)
	{
		if (buffer[0] == '\n')
			return (1);
		buffer[1] = 0;
		temp = ft_strjoin(*line, buffer);
		if (!temp)
			return (-1);
		free(*line);
		*line = temp;
	}
	if (read_ret < 0)
		return (-1);
	return (0);
}
