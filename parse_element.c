/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:21:29 by smia              #+#    #+#             */
/*   Updated: 2022/06/21 00:26:34 by smia             ###   ########.fr       */
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
    sc->amb.ratio = ft_atof(tockens[1]);
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
    sc->cam.fov = ft_atof(tockens[3]);
    
}

void    parse_light(t_scene *sc, char **tockens)
{
    if (!tockens || !tockens[1] || !tockens[2] || tockens[3])
        ft_err("invalid light !");
    if (sc->light.count != 0)
        ft_err("to many light !");
    sc->light.count++;
    sc->light.src = get_vec(tockens[1]);
    sc->light.ratio = ft_atof(tockens[2]);
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
    obj->p.x = ft_atof(tockens[2]);
    // if (obj->p.x < 0)
    //     ft_err("***")
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
    obj->p.x = ft_atof(tockens[3]);
    obj->p.y = ft_atof(tockens[4]);
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
    obj->col = get_color(tockens[3]);
}