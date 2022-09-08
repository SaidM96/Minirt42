/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:47 by smia              #+#    #+#             */
/*   Updated: 2022/09/08 21:22:20 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// #include "camera.h"

t_camera    set_camera(t_scene *sc)
{
    t_camera cam;

    cam.aspect_r = (double) WIDTH / (double) HEIGHT;
    
    cam.theta = sc->cam.fov * M_PI / 180.0;
    cam.height = tan(cam.theta / 2);
    cam.width = cam.aspect_r * cam.height;
    cam.forward = sc->cam.dir;
    cam.up = get_normalized(vect_cross(cam.forward, make_vec(0.0,1.0,0.0)));
    cam.right = get_normalized(vect_cross(cam.forward, cam.up));
    return (cam);
}

t_CamRay       ray_primary(t_camera *cam, double u, double v)
{
    t_CamRay   ray;
    
    ray.origin = cam->orig;

    ray.dir = add_vec(add_vec(mult_vec(cam->up, u * cam->height), mult_vec(cam->right, v * cam->width)),cam->forward);
    ray.dir = get_normalized(ray.dir);
    return (ray);
}



void    ft_render(t_scene *sc)
{
	void		*mlx;
	void		*mlx_win;
	img_data	img;
	
	double		v, u;
	t_camera	cam;
	t_CamRay	ray_;

	cam = set_camera(sc);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int i = 0 ; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			v = (double)i * 2 / HEIGHT - 1;
			u = (double)j * 2 / WIDTH - 1;
			ray_ = ray_primary(&cam, u, v);
            // printf("%f %f %f\n", ray_.dir.x, ray_.dir.y, ray_.dir.z);
			//_ray = ray_color(&ray_);
			//color_p = ray_color(&ray);
        //    printf("%f\n", find_inter(&ray_, &sc->objs));
            t_inter x = find_inter(&ray_, sc);
            // printf("%f \n", x);
            if (x.t > 0 ) // this line must return color of pixel (x,y)
                my_mlx_pixel_put(&img, j, i, createRGB(x.col.x, x.col.y, x.col.z));
			else
				my_mlx_pixel_put(&img, j, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}