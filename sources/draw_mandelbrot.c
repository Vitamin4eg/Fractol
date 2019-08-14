/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:32:00 by nbethany          #+#    #+#             */
/*   Updated: 2019/07/24 21:32:01 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../fractol.h"

void init_mandelbrot(t_fractal *fractal)
{
	fractal->name = 1;
	fractal->x1 = -2.8;
	fractal->y1 = -2.3;
	fractal->zoom = 200;
	fractal->max_it = 50;
	fractal->color = 265;
}

void	mandelbrot_calc(t_fractal *data)
{
	data->cRe = data->x / data->zoom + data->x1;
	data->cIm = data->y / data->zoom + data->y1;
	data->zRe = 0;
	data->zIm = 0;
	data->cur_it = 0;
	while (data->zRe * data->zRe + data->zIm * data->zIm < 4 && data->cur_it < data->max_it)
	{
		data->tmp = data->zRe;
		data->zRe = data->zRe * data->zRe - data->zIm * data->zIm + data->cRe;
		data->zIm = 2 * data->tmp * data->zIm + data->cIm;
		data->cur_it++;
	}
	get_color(data);
}

void	*mandelbrot(void *data)
{
	int		tmp;
	t_fractal	*fractal;

	fractal = (t_fractal *)data;
	fractal->x = 0;
	tmp = fractal->y;
	while (fractal->x < WIDTH)
	{
		fractal->y = tmp;
		while (fractal->y < fractal->y_max)
		{
			mandelbrot_calc(fractal);
			fractal->y++;
		}
		fractal->x++;
	}
	return (data);
}