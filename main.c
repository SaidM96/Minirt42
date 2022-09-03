/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:35:29 by smia              #+#    #+#             */
/*   Updated: 2022/09/03 13:23:17 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    ft_render(t_scene *sc)
{
	void		*mlx;
	void		*mlx_win;
	img_data	img;
	
	double		v, u;
	//t_vec		dir;
	t_canvas	canv;
	t_camera	cam;
	//t_CamRay	ray;
	t_CamRay	ray_;
	//t_vec		_ray;


	(void)sc;
	canv = canvas(WIDTH, HEIGHT);
	cam = camera(&canv, sc->cam.cen);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int i = canv.height - 1; i >= 0; i--)
	{
		for (int j = 0; j < canv.width; j++)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			//ray_ = ray(make_vec(0.0, 0.0, 0.0), dir);
			ray_ = ray_primary(&cam, u, v);
			//_ray = ray_color(&ray_);
			//color_p = ray_color(&ray);
            if (find_inter(&ray_, &sc->objs) > 0) // this line must return color of pixel (x,y)
            {
                my_mlx_pixel_put(&img, j, i, 0x00FF0000);
            }
			else
				my_mlx_pixel_put(&img, j, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
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
        ft_err("wrong args : Please try enter filename.rt");
    fd = open(av[1], O_RDONLY);
    sc = alloc_scence();
    if (!sc)
        ft_err("allocation");
    parse(sc,fd);
    ft_render(sc);
    
    ft_collect(&root,root);
    return 0;
}