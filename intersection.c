/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:00:32 by smia              #+#    #+#             */
/*   Updated: 2022/09/03 13:22:47 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double inter_sphere(t_CamRay *ray, t_objs *sp)
{
    double   a;
    double   b;
    double   c;
    double   discr;
    double   dist1;
    double   dist2;
    t_vec   cam_sphere;

    dist1 = 0;
    dist2 = 0;
    cam_sphere = sub_vec(sp->cen, ray->origin);
    a = dot_product(ray->dir,ray->dir); 
    b = 2 * dot_product(cam_sphere,ray->dir);
    c = dot_product(cam_sphere, cam_sphere) - (sp->p.x / 2) * (sp->p.x / 2);
    discr = b * b - (4 * a * c);
    if (discr < 0)
        return (0);
    dist1 = (b * (-1) - sqrt(discr)) / (2 * a);
    dist2 = (b * (-1) + sqrt(discr)) / (2 * a);
    if (dist1 * dist2 >= 0)
    {
        if (dist1 >= 0)
            return take_min(dist1, dist2);
        return -1;
    }
    if (dist1 >= 0)
        return dist1;
    return dist2;
}

double inter_plane(t_CamRay *ray, t_objs *pl)
{
    t_vec   cam_plane;
    double  dist;
    if (dot_product(pl->dir,ray->dir) == 0)
        return 0; 
    cam_plane = sub_vec(pl->cen, ray->origin);
    dist = dot_product(pl->dir, cam_plane) / dot_product(pl->dir,ray->dir);
    if (dist >= 0)
        return dist;
    else
        return -1;
}

// double inter_cylinder(t_CamRay *ray, t_objs *cy)
// {
    
// }

double find_inter(t_CamRay *ray, t_objs **objs)
{
    double  dist;
    double  hdist;
    hdist = -1;
    t_objs  *tmp;
    tmp = *objs;
    
    while (tmp)
    {
        if (tmp->type == SP)
        {
            dist = inter_sphere(ray,tmp);
            if (hdist > dist || hdist == -1)
                hdist = dist;
        }
        // if (tmp->type == PL)
        // {
        //     dist = inter_plane(ray, tmp);
        //     if (hdist > dist || hdist == -1)
        //         hdist = dist;
        // }
        // if (tmp->type == CY)
        // {
        //     inter_cylinder(ray, tmp);
        //     if (hdist > dist || hdist == -1)
        //         hdist = dist;
        // }
        tmp = tmp->next;
    }
    return (hdist);
}
