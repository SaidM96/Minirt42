/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:35:29 by smia              #+#    #+#             */
/*   Updated: 2022/06/22 04:48:31 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
    // ray_tracing();
    free_all(sc);
    return 0;
}