/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:34:13 by smia              #+#    #+#             */
/*   Updated: 2022/06/21 03:51:47 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ft_res(char *str, int i)
{
	int		j;
	double	res;

	res = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	j = 0;
	if (str[i] == '.')
	{
		i++;
		while (str[i] <= '9' && str[i] >= '0' && j <= 3)
		{
			res = res + (double)((str[i] - '0')
					/ pow(10.0, (double)++j));
			i++;
		}
	}
	return (res);
}

double		ft_atof(char *str)
{
	int		i;
	int		signe;
	double	res;

	i = 0;
	res = 0;
	signe = 1;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		signe = str[i] == '-' ? -1 : 1;
		i++;
	}
	res = ft_res(str, i);
	return (res * signe);
}