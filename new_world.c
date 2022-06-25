/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:36:43 by smia              #+#    #+#             */
/*   Updated: 2022/06/25 22:23:16 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    trans_all(t_scene *sc, t_matrix *m)
{
    t_objs      *objs;
    t_matrix    *m_cy;

    objs = sc->objs;
	trans_point(&(sc->light.src), m); 
	while (objs)
    {
        if (objs->type == SP)
            trans_point(&(objs->cen), m);
        if (objs->type == PL)
        {
            trans_point(&(objs->cen), m);
            trans_vdir(objs->dir, m);
        }
        if(objs->type == CY)
        {
            trans_point(&(objs->cen), m);
            trans_vdir(&(objs->dir), m);
            m_cy = get_trans_matrix(objs->cen, objs->dir);
            // trans_point(o, m_cy);
            free(m_cy);
        }
        objs = objs->next;
    }
    trans_vdir(&(objs->dir), m);
    trans_point(&(objs->cen), m);
    
}

void    new_world(t_scene *sc)
{
    sc->m_trans = get_trans_matrix(sc->cam.dir, sc->cam.cen);
    trans_all(sc, sc->m_trans); 
}