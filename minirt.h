/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:01:02 by smia              #+#    #+#             */
/*   Updated: 2022/06/21 00:26:48 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1200
# define HEIGHT 1000
# define CY 1
# define PL 2
# define SP 3
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct  s_vec
{
    double  x;
    double  y;
    double  z;
}               t_vec;

typedef struct  t_cam
{
    t_vec   cen;
    t_vec   dir;
    double  fov;
    int     count;
}               t_cam;

typedef struct  s_light
{
    t_vec   src;
    double  ratio;
    int     count;
}               t_light;

typedef struct s_amb
{
    t_vec   col;
    double  ratio;
    int     count;
}   t_amb;

typedef struct  s_objs
{
    int            type;
    t_vec           cen;
    t_vec           dir;
    t_vec           p;
    t_vec           col;
    t_vec           norm;
    struct s_objs   *next;
}               t_objs;

typedef struct s_scene
{
    t_vec   col;
    t_vec   up_vec;
    t_cam   cam;
    t_light light;
    t_amb   amb;
    t_objs  *objs;
}               t_scene;

void	ft_err(char *err);
int     check_file(int ac, char **av);
// parse

void    parse(t_scene *sc, int fd);
void    parse_line(char *id, char **tockens, t_scene *sc);
void    parse_plane(t_scene *sc, char **tockens);
void    parse_cylinder(t_scene *sc, char **tockens);
void    parse_sphere(t_scene *sc, char **tockens);
void    parse_light(t_scene *sc, char **tockens);
void    parse_camera(t_scene *sc,char **tockens);
void    parse_ambient(t_scene *sc, char **tockens);


// allocation
t_scene *alloc_scence(void);
t_objs  *alloc_obj(t_objs   **objs);

int	ft_strlen(const char *str);
char	*gnl(int fd);
double	ft_atof(char *str);
char	**ft_split(const char *str, char c);
void	free_split(char **s);
void	init_vec(t_vec *v);
t_vec   get_vec(char *s);
t_vec   get_color(char *s);


#endif