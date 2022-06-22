/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:12:52 by smia              #+#    #+#             */
/*   Updated: 2022/06/22 04:48:51 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_err(char *err)
{
	printf("Error : %s\n", err);
	exit(1);
}

t_scene *alloc_scence(void)
{
    t_scene *sc;

    sc = malloc((sizeof(t_scene)));
    if (!sc)
        return (NULL);
	sc->objs = NULL;
    sc->amb.count = 0;
    sc->cam.count = 0;
    sc->light.count = 0;
    return (sc);
}

t_objs  *alloc_obj(t_objs   **objs)
{
    t_objs  *new_obj;

    new_obj = malloc(sizeof(t_objs));
    if (!new_obj)
        return (NULL);
    null_vec(&(new_obj->col));
    null_vec(&(new_obj->cen));
    null_vec(&(new_obj->dir));
    null_vec(&(new_obj->p));
    new_obj->next = *objs;
    *objs = new_obj;
    return (new_obj);
}

void		ft_lstdel(t_objs **objs)
{
	t_objs	*temp;

	if (!objs)
		return ;
	while (*objs)
	{
		temp = (*objs)->next;
		free(*objs);
		*objs = temp;
	}
	*objs = NULL;
	return ;
}

void    free_all(t_scene *sc)
{
    ft_lstdel(&(sc->objs));
    free(sc);
}