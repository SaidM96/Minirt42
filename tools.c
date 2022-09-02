/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:34:13 by smia              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/02 15:06:40 by smia             ###   ########.fr       */
=======
/*   Updated: 2022/09/01 16:33:15 by smia             ###   ########.fr       */
>>>>>>> 50748cb3512a062af8a85e1908aa038b62d8d09b
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double take_min(double x, double y)
{
	if (x > y)
		return y;
	return (x);
}
void add_dist(double *dist, double d)
{
	int  i = 0;
<<<<<<< HEAD
	// while (dist[i] != -1)
	// 	i++;
=======
	while (dist[i] != -1)
		i++;
>>>>>>> 50748cb3512a062af8a85e1908aa038b62d8d09b
	dist[i] = d;
}

double	ft_atod(const char *str)
{
	double	nb;
	int		signe;
	int		i;
	int		aux;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	signe = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	if (str[i] != '.')
		return ((double)nb * signe);
	aux = 10;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		nb = nb + (double)(str[i] - '0') / aux;
		aux = aux * 10;
	}
	return ((double)nb * signe);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	nb;

	i = 0;
	nb = 0;
	signe = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * signe);
}
