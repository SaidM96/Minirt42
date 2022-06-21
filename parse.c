/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:22:01 by smia              #+#    #+#             */
/*   Updated: 2022/06/21 00:25:49 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec   get_color(char *s)
{
    char    **params;
    t_vec   cord;
    
    params = ft_split(s, ',');
    if (!params || !params[1] || !params[1] || params[3])
        ft_err("invalid color!");
    cord = (t_vec){(int)ft_atof(params[0]), (int)ft_atof(params[1]), (int)ft_atof(params[2])};
    if (cord.x > 255 || cord.y > 255 || cord.z > 255)
        ft_err("invalid color");
    if (cord.x < 0 || cord.y < 0 || cord.z < 0)
        ft_err("invalid color");
    free_split(params);
    return (cord);
}

t_vec   get_vec(char *s)
{
    char    **params;
    t_vec   cord;
    
    params = ft_split(s, ',');
    if (!params || !params[1] || !params[1] || params[3])
        ft_err("invalid coordinates");
    cord = (t_vec){ft_atof(params[0]), ft_atof(params[1]), ft_atof(params[2])};
    free_split(params);
    return (cord);        
}

t_objs  *alloc_obj(t_objs   **objs)
{
    t_objs  *new_obj;

    new_obj = malloc(sizeof(t_objs));
    if (!new_obj)
        return (NULL);
    init_vec(&(new_obj->col));
    init_vec(&(new_obj->cen));
    init_vec(&(new_obj->dir));
    init_vec(&(new_obj->p));
    new_obj->next = *objs;
    *objs = new_obj;
    return (new_obj);
}

void    parse_line(char *id, char **tockens, t_scene *sc)
{
    
    if (id[0] == 'A' && id[1] == '\0')
        parse_ambient(sc, tockens);
	else if (id[0] == 'C' && id[1] == '\0')
		parse_camera(sc, tockens);
	else if (id[0] == 'L' && id[1] == '\0')
	    parse_light(sc, tockens);
	else if (id[0] == 's' && id[1] == 'p' && id[2] == '\0')
		parse_sphere(sc, tockens);
	else if (id[0] == 'p' && id[1] == 'l' && id[2] == '\0')
		parse_plane(sc, tockens);
	else if (id[0] == 'c' && id[1] == 'y' && id[2] == '\0')
		parse_cylinder(sc, tockens);
	else
		ft_err("invalid object type");
}

void    parse(t_scene *sc, int fd)
{
    char    **tockens;

    while (1337)
    {
        tockens = ft_split(gnl(fd), ' ');
        if (tockens == NULL)
            break ;
        if (*tockens)
            parse_line(*tockens, tockens, sc);
        free_split(tockens);
    }
    close(fd);
}