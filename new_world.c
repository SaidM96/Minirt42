/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:36:43 by smia              #+#    #+#             */
/*   Updated: 2022/06/29 21:32:49 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	trans_point(t_vec *p, t_matrix *m)
{
	t_vec	p1;

	p1 = *p;
	p->x = (m->l1.a1 * p1.x) + (m->l1.a2 * p1.y)
		+ (m->l1.a3 * p1.z) + (m->l1.a4);
	p->y = (m->l2.a1 * p1.x) + (m->l2.a2 * p1.y)
		+ (m->l2.a3 * p1.z) + (m->l2.a4);
	p->z = (m->l3.a1 * p1.x) + (m->l3.a2 * p1.y)
		+ (m->l3.a3 * p1.z) + (m->l3.a4);
}

void	trans_vdir(t_vec *v, t_matrix *m)
{
	t_vec	o;

	o = *v;
	trans_point(&o, m);
	v->x = o.x - m->l1.a4;
	v->y = o.y - m->l2.a4;
	v->z = o.z - m->l3.a4;
}

void    trans_all(t_scene *sc, t_matrix *m)
{
    t_objs      *objs;

    objs = sc->objs;
	trans_point(&(sc->light.src), m); 
	while (objs)
    {
        if (objs->type == SP)
            trans_point(&(objs->cen), m);
        if (objs->type == PL)
        {
            trans_point(&(objs->cen), m);
            trans_vdir(&(objs->dir), m);
        }
        if(objs->type == CY)
        {
            trans_point(&(objs->cen), m);
            trans_vdir(&(objs->dir), m);
        }
        objs = objs->next;
    }
    trans_vdir(&(sc->cam.dir), m);
    trans_point(&(sc->cam.cen), m);
}

void    new_world(t_scene *sc)
{
    sc->m_trans = get_trans_matrix(sc->cam.dir, sc->cam.cen);
    trans_all(sc, sc->m_trans);
}

