/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:35:29 by smia              #+#    #+#             */
/*   Updated: 2022/06/21 03:14:47 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	sc->up_vec.x = 0;
	sc->up_vec.y = -1;
	sc->up_vec.z = 0;
    return (sc);
}

int check_file(int ac, char **av)
{
    int i;
    int fd;
    
    fd = 0;
    if (ac != 2 )
        return (1);
    if (!av[1])
        return (1);
    i = ft_strlen(av[1]);
    if (i < 4)
        return (1);
    if (av[1][i - 1] == 't' || av[1][i - 2] == 'r' || av[1][i - 3] == '.')
    {
        fd = open(av[1], O_RDONLY);
        if (fd < 0)
            return (1);
    close(fd);
    }
    else
        return (1);
    return (0);
}

int main (int ac, char **av)
{
    t_scene *sc;
    int     fd;

    if (check_file(ac, av))
        ft_err("wrong args or file");
    fd = open(av[1], O_RDONLY);
    sc = alloc_scence();
    if (!sc)
        ft_err("allocation");
    parse(sc,fd);
    printf("%f   %f    %f \n",sc->amb.col.x, sc->amb.col.y, sc->amb.col.z);
    while (sc->objs)
    {
        printf("%d ||", sc->objs->type);
        sc->objs =  sc->objs->next;
    }
    free_all(sc);
    return 0;
}