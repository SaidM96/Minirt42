/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:47 by smia              #+#    #+#             */
/*   Updated: 2022/09/05 18:52:28 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// #include "camera.h"

t_CamRay	ray(t_vec orig, t_vec dir)
{
    t_CamRay ray;

    ray.origin = orig;
    ray.dir = get_normalized(dir);
    return (ray);
}

t_vec	ray_at(t_CamRay *ray, double t)
{
    t_vec	at;

    at = add_vec(ray->origin, mult_vec(ray->dir, t));
    return (at);
}

t_camera    camera(t_canvas *canvas, t_scene *sc)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;
  
    viewport_height = tan(sc->cam.fov * M_PI / 180);
    focal_len = 1.0;
    cam.orig = sc->cam.cen;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = make_vec(cam.viewport_w, 0, 0);
    cam.vertical = make_vec(0, cam.viewport_h, 0);
    // lower left corner point coordinates, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    cam.left_bottom = sub_vec(sub_vec(sub_vec(cam.orig, div_vect(cam.horizontal, 2)),
                                div_vect(cam.vertical, 2)), make_vec(0, 0, focal_len));
    return (cam);
}

t_CamRay       ray_primary(t_camera *cam, double u, double v)
{
    t_CamRay   ray;

    ray.origin = cam->orig;
    //unit vector
    ray.dir = get_normalized(sub_vec(add_vec(add_vec(cam->left_bottom, mult_vec(cam->horizontal, u)), mult_vec(cam->vertical, v)), cam->orig));
    return (ray);
}

t_vec	color(double r, double g, double b)
{
	t_vec color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

t_vec	ray_color(t_CamRay *r)
{
    double  t;
    
    t = 0.5 * (r->dir.y + 1.0);
    return (add_vec(mult_vec(color(1, 1, 1), 1.0 - t), mult_vec(color(0.5, 0.7, 1.0), t)));
}

t_canvas    canvas(int width, int height)
{
    t_canvas    canv;

    canv.height = height;
    canv.width = width;
    canv.aspect_ratio = canv.width / canv.height;
    return (canv);
}

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
	cam = camera(&canv, sc);
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