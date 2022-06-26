/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:36:43 by smia              #+#    #+#             */
/*   Updated: 2022/06/26 02:01:41 by smia             ###   ########.fr       */
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

void	trans_vdir(t_vec *element, t_matrix *m)
{
	t_vec	o;

	o = *element;
	update_cogo_element(&o, m);
	element->x = o.x - m->l1.a4;
	element->y = o.y - m->l2.a4;
	element->z = o.z - m->l3.a4;
}

void    trans_all(t_scene *sc, t_matrix *m)
{
    t_objs      *objs;
    t_vec       null;
    t_vec       o;

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
            objs->m_trans = get_trans_matrix(objs->cen, objs->dir);
            trans_point(&o, objs->m_trans);
		    objs->o_c = sub_vec(o, null);
		    objs->z_o = o.z;
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