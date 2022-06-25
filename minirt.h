/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:01:02 by smia              #+#    #+#             */
/*   Updated: 2022/06/25 22:23:37 by smia             ###   ########.fr       */
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

typedef struct  s_vec
{
    double  x;
    double  y;
    double  z;
}               t_vec;

// matrix 

typedef struct  s_line 
{
    double  a1;
    double  a2;
    double  a3;
    double  a4;
}               t_line;

typedef struct s_matrix
{
    t_line  l1;
    t_line  l2;
    t_line  l3;
    t_line  l4;
}               t_matrix;


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
    int             type;
    t_vec           cen;
    t_vec           dir;
    t_vec           p;
    t_vec           col;
    t_vec           norm;
    struct s_objs   *next;
}               t_objs;

typedef struct s_scene
{
    t_vec       col;
    t_cam       cam;
    t_light     light;
    t_amb       amb;
    t_objs      *objs;
    t_matrix    *m_trans;
}               t_scene;

typedef struct s_mlx
{
    void	*win;
	void	*mlx;
	void	*img;
    int     endn;
    
}               t_mlx;

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
t_scene     *alloc_scence(void);
t_objs      *alloc_obj(t_objs   **objs);
void	    t_lstdel(t_objs **objs);
void        free_all(t_scene *sc);
t_matrix    *alloc_matrix(void);

// tools
int	    ft_strlen(const char *str);
char	*gnl(int fd);
double	ft_atod(const char *str);
int	    ft_atoi(const char *str);
char	**ft_split(const char *str, char c);
void	free_split(char **s);

//vectors
void	    null_vec(t_vec *v);
t_vec       get_vec(char *s);
t_vec       get_color(char *s);
t_vec		get_normalized(t_vec v);
void		normalize(t_vec *v);
double		get_norm2(t_vec v);
t_vec		sub_vec(t_vec u, t_vec v);
t_vec		add_vec(t_vec u, t_vec v);
t_vec	    mult_vec(t_vec v, double a);
t_vec		vect_cross(t_vec u, t_vec v);
double	    dot_product(t_vec u, t_vec v);

// matrix
void        null_matrix(t_matrix *matrix);
void        null_line_matrix(t_line l);
t_matrix    *get_trans_matrix(t_vec v_org, t_vec v_dir);
t_matrix    *get_inverse(t_matrix *t_m);
void        get_R_matrix(t_matrix *m, t_matrix *Rx, t_matrix *Ry);
void        calcul_Rx_Ry(t_vec v_dir, t_matrix *Rx, t_matrix *Ry);
double      get_angle_x(double y, double z, double angle);
double	    get_angle_y(double x, double z, double angle);

// Raytracing
void    new_world(t_scene *sc);

#endif