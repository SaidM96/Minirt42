/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:00:32 by smia              #+#    #+#             */
/*   Updated: 2022/09/02 13:26:23 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int inter_sphere(t_ray *ray, t_cam cam, t_objs *sp)
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
    cam_sphere = sub_vec(sp->cen, cam.cen);
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
        {
            add_dist(ray->dist, take_min(dist1, dist2));
            return 1;
        }
        return 0;
    }
    if (dist1 >= 0)
    {
        add_dist(ray->dist, dist1);
        return 1;
    }
    add_dist(ray->dist, dist2);
    return 1;
}

int inter_plane(t_ray *ray, t_cam cam, t_objs *pl)
{
    t_vec   cam_plane;
    double dist;
    if (dot_product(pl->dir,ray->dir) == 0)
        return 0; 
    cam_plane = sub_vec(pl->cen, cam.cen);
    dist = dot_product(pl->dir, cam_plane) / dot_product(pl->dir,ray->dir);
    if (dist >= 0)
    {
        add_dist(ray->dist, dist);
        return 1;
    }
    else
        return 0;
}

int inter_cylinder(t_ray *ray, t_cam cam, t_objs *pl)
{
    
}
