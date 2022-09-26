/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:22 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/26 22:03:12 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	specular(t_scene *sc, t_inter inter, t_light *light)
{
	t_vec 	L;
	t_vec 	V;
	t_vec	R;
	double	spec;
	t_vec	hit_light;

	hit_light = sub_vec(light->src, inter.hit);
	L = get_normalized(hit_light);
	V = get_normalized(sub_vec(inter.hit, sc->cam.cen));
	R = sub_vec(mult_vec(inter.norm, 2 * dot_product(inter.norm, L)), L);
	spec = pow(dot_product(R,V),50) * light->ratio * 0.5;
	return (mult_vec(light->col, spec));
}