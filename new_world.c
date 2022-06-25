/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:36:43 by smia              #+#    #+#             */
/*   Updated: 2022/06/25 11:18:58 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    new_world(t_scene *sc)
{
    sc->m_trans = get_trans_matrix(sc->cam.dir, sc->cam.cen);
    // with trans matrix we can move all our vectors 
}