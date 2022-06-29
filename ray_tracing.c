/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:16:02 by smia              #+#    #+#             */
/*   Updated: 2022/06/29 21:37:39 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_ray(t_scene *sc, t_vec *ray)
{
	ray->z = 1;
	ray->y = tan((sc->cam.fov / 2) * (M_PI / 180));
	ray->x = -ray->y;
}

int     pixel_color(t_scene *sc, t_vec ray, double stp)
{
    // 1 - function that find the closest point intersection with the ray
    // 2 - calcul the color
}

void	ray_tracing(t_scene *sc, t_mlx *mlx)
{
	int		x;
	int		y;
	t_vec	ray;
	double	stp;
	double	hold_x;

	y = -1;
	init_ray(sc, &ray);
	stp = fabs(ray.x * 2) / 1000;
	hold_x = ray.x;
	while (++y < 1000)
	{
		x = -1;
		ray.x = hold_x;
		while (++x < 1000)
		{
			ray.x += stp;
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, pixel_color(sc, ray, stp));
		}
		ray.y -= stp;
	}
}