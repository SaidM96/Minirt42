/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:28:18 by smia              #+#    #+#             */
/*   Updated: 2022/06/25 11:15:18 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    calcul_Rx_Ry(t_vec v_dir, t_matrix *Rx, t_matrix *Ry)
{
    // angles
    double  a;
    double  b;

    // fill rotation matrix selon y : Ry 
    if (v_dir.x || v_dir.z)
        a = acos(fabs(v_dir.z) / sqrt(pow(v_dir.z, 2)
				+ pow(v_dir.x, 2)));
    a = get_angle_y(v_dir.x, v_dir.z, a);
    Ry->l1.a1 = cos(a);
    Ry->l1.a3 = sin(a);
    Ry->l2.a2 = 1;
    Ry->l3.a1 = -sin(a);
    Ry->l3.a3 = cos(a);
    Ry->l4.a4 = 1;
    v_dir.z = fabs(v_dir.z);
    // fill rotation matrix selon x : Rx
    b = acos(sqrt(pow(module_v(v_dir), 2)
			- pow(v_dir.y, 2)) / module_v(v_dir));
    b = get_angle_x(v_dir.y, v_dir.z, b);
    Rx->l1.a1 = 1;
    Rx->l2.a2 = cos(b);
    Rx->l2.a3 = -sin(b);
    Rx->l3.a2 = sin(b);
    Rx->l3.a3 = cos(b);
    Ry->l4.a4 = 1;
}

void    get_R_matrix(t_matrix *m, t_matrix *Rx, t_matrix *Ry)
{
    m->l1.a1 = (Ry->l1.a1 * Rx->l1.a1) + (Ry->l1.a2 * Rx->l2.a1)
			+ (Ry->l1.a3 * Rx->l3.a1) + (Ry->l1.a4 * Rx->l4.a1);
    m->l2.a2 = (Ry->l2.a1 * Rx->l1.a2) + (Ry->l2.a2 * Rx->l2.a2)
			+ (Ry->l2.a3 * Rx->l3.a2) + (Ry->l2.a4 * Rx->l4.a2);
    m->l3.a3 = (Ry->l3.a1 * Rx->l1.a3) + (Ry->l3.a2 * Rx->l2.a3)
			+ (Ry->l3.a3 * Rx->l3.a3) + (Ry->l3.a4 * Rx->l4.a3);
    m->l4.a4 = (Ry->l4.a1 * Rx->l1.a4) + (Ry->l4.a2 * Rx->l2.a4)
			+ (Ry->l4.a3 * Rx->l3.a4) + (Ry->l4.a4 * Rx->l4.a4);
}

t_matrix    *get_trans_matrix(t_vec v_org, t_vec v_dir)
{
    t_matrix	*Ry;
	t_matrix	*Rx;
	t_matrix	*t_m;
	t_matrix	*m;

	t_m = NULL;
	m = NULL;
	Ry = NULL;
	Rx = NULL;
	t_m = alloc_matrix();
	Ry = alloc_matrix();
	Rx = alloc_matrix();
    calcul_Rxy_matrix(v_dir, Rx, Ry);
    get_R_matrix(t_m, Rx, Ry);
    t_m->l1.a4 = v_org.x;
    t_m->l2.a4 = v_org.y;
    t_m->l3.a4 = v_org.z;
    m = get_inverse(t_m);
    free(t_m);
    free(Rx);
    free(Ry);
    return (m);
}