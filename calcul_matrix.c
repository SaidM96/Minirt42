/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 02:26:23 by smia              #+#    #+#             */
/*   Updated: 2022/06/29 21:42:11 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    null_line_matrix(t_line l)
{
    l.a1 = 0;
    l.a2 = 0;
    l.a3 = 0;
    l.a4 = 0;
}

void    null_matrix(t_matrix *matrix)
{
     null_line_matrix(matrix->l1);
     null_line_matrix(matrix->l2);
     null_line_matrix(matrix->l3);
     null_line_matrix(matrix->l4);
}

t_matrix    *alloc_matrix(void)
{
    t_matrix    *matrix;

    matrix = malloc(sizeof(t_matrix));
    if (!matrix)
        ft_err("allocation matrix");
    null_matrix(matrix);
    return (matrix);
}

double	get_angle_y(double x, double z, double angle)
{
	if ((x < 0) && (z >= 0))
		angle = (2 * M_PI) - angle;
	else if ((x > 0) && (z < 0))
		angle = M_PI - angle;
	else if ((x <= 0) && (z < 0))
		angle = M_PI + angle;
    return (angle);
}

double  get_angle_x(double y, double z, double angle)
{
    if ((y > 0) && (z >= 0))
		angle = (2 * M_PI) - angle;
	else if ((y > 0) && (z < 0))
		angle = M_PI + angle;
	else if ((y < 0) && (z < 0))
		angle = M_PI - angle;
    return (angle);
}

t_matrix    *get_inverse(t_matrix *t_m)
{
    t_matrix    *m;

    m = alloc_matrix();
    m->l1.a1 = t_m->l1.a1;
    m->l1.a4 = -(t_m->l1.a4 * t_m->l1.a1);
    m->l2.a2 = t_m->l2.a2;
    m->l2.a4 = -(t_m->l2.a4 * t_m->l2.a2);
    m->l3.a3 = t_m->l3.a3;
    m->l3.a4 = -(t_m->l3.a4 * t_m->l3.a3);
    m->l4.a4 = 1;
    return (m);
}