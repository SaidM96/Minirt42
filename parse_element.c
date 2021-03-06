/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:21:29 by smia              #+#    #+#             */
/*   Updated: 2022/06/26 03:12:49 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    parse_ambient(t_scene *sc, char **tockens)
{
    if (!tockens || !tockens[1] || !tockens[2] || tockens[3])
        ft_err("invalid ambiant!");
    if (sc->amb.count != 0)
        ft_err("too many ambiant");
    sc->amb.count++;
    sc->amb.ratio = ft_atod(tockens[1]);
    if (sc->amb.ratio < 0 || sc->amb.ratio > 1)
        ft_err("enter ambient lighting ratio in range [0.0,1.0]");
    sc->amb.col = get_color(tockens[2]);
}


void    parse_camera(t_scene *sc,char **tockens)
{
    if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
        ft_err("invalid camera !");
    if (sc->cam.count != 0)
        ft_err("too many camera");
    sc->cam.count++;
    sc->cam.cen = get_vec(tockens[1]);
    sc->cam.dir = get_vec(tockens[2]);
    if (sc->cam.dir.x > 1 || sc->cam.dir.y > 1 || sc->cam.dir.z > 1)
        ft_err("invalid orientation camera");
    if (sc->cam.dir.x < -1 || sc->cam.dir.y < -1 || sc->cam.dir.z < -1)
        ft_err("invalid orientation camera");
    if (sc->cam.dir.x == 0 || sc->cam.dir.y == 0 || sc->cam.dir.z == 0)
        ft_err("invalid orientation camera");
    sc->cam.fov = ft_atod(tockens[3]);
    if (sc->cam.fov < 0 || sc->cam.fov > 180)
        ft_err("FOV  in range [0,180]");
}

void    parse_light(t_scene *sc, char **tockens)
{
    if (!tockens || !tockens[1] || !tockens[2] || tockens[3])
        ft_err("invalid light !");
    if (sc->light.count != 0)
        ft_err("to many light !");
    sc->light.count++;
    sc->light.src = get_vec(tockens[1]);
    sc->light.ratio = ft_atod(tockens[2]);
    if (sc->light.ratio < 0 || sc->light.ratio > 1)
        ft_err("enter the light brightness ratio in range [0.0,1.0]");
}

void    parse_sphere(t_scene *sc, char **tockens)
{
    t_objs  *obj;
    
    if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
        ft_err("invalid sphere");
    obj = alloc_obj(&(sc->objs));
    obj->type = SP;
    obj->cen = get_vec(tockens[1]);
    obj->p.x = ft_atod(tockens[2]);
    if (obj->p.x <= 0)
        ft_err("invalid diameter sphere");
    obj->col = get_color(tockens[3]);
}

void    parse_cylinder(t_scene *sc, char **tockens)
{
    t_objs  *obj;
    
    if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || !tockens[4] || !tockens[5] || tockens[6])
        ft_err("invalid cylinder");
    obj = alloc_obj(&(sc->objs));
    obj->type = CY;
    obj->cen = get_vec(tockens[1]);
    obj->dir = get_vec(tockens[2]);
    if (obj->dir.x > 1 || obj->dir.y > 1 || obj->dir.z > 1)
        ft_err("invalid orientation cylinder");
    if (obj->dir.x < -1 || obj->dir.y < -1 || obj->dir.z < -1)
        ft_err("invalid orientation cylinder");
    obj->p.x = ft_atod(tockens[3]);
    obj->p.y = ft_atod(tockens[4]);
    if (obj->p.x <= 0 || obj->p.y <= 0)
        ft_err("invalid diameter cy");
    obj->col = get_color(tockens[5]);
}

void    parse_plane(t_scene *sc, char **tockens)
{
    t_objs  *obj;
    
    if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
        ft_err("invalid plane!");
    obj = alloc_obj(&(sc->objs));
    obj->type = PL;
    obj->cen = get_vec(tockens[1]);
    obj->dir = get_vec(tockens[2]);
    if (obj->dir.x > 1 || obj->dir.y > 1 || obj->dir.z > 1)
        ft_err("invalid orientation plane");
    if (obj->dir.x < -1 || obj->dir.y < -1 || obj->dir.z < -1)
        ft_err("invalid orientation plane");
    obj->col = get_color(tockens[3]);
}