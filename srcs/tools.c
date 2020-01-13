/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/04 22:12:22 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

float			rsqrt(float number)
{
	float	i;
	float	threehalfs;
	t_rsqrt	conv;

	i = number * 0.5f;
	threehalfs = 1.5f;
	conv = (t_rsqrt){ number };
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (i * conv.f * conv.f));
	return (conv.f);
}

static void		free_usages(t_cube *data)
{
	int	i;

	if (data->str)
		ft_strdel(&data->str);
	if (data->vector.vertex)
		ft_memdel((void **)&data->vector.vertex);
	i = -1;
	while (++i < data-> ac - 1)
	{
		if (data->tab && data->tab[i])
			ft_memdel((void **)&data->tab[i]);
		if (data->mesh[i].object)
			ft_memdel((void **)&data->mesh[i].object);
	}
}

void			clean_exit(t_cube *data, char *str, int token)
{
	if (data)
	{
		free_usages(data);
		if (data->pwindow)
		{
			if (data->screen)
				SDL_FreeSurface(data->screen);
			if (data->renderer)
				SDL_DestroyRenderer(data->renderer);
			SDL_DestroyWindow(data->pwindow);
			SDL_Quit();
		}
		data = NULL;
	}
	if (str)
		ft_putendl_fd(str, 2);
	exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}

void			drawtriangle(t_cube *data, t_triangle triangle, int color)
{
	drawline(data, triangle.v[0], triangle.v[1], color);
	drawline(data, triangle.v[1], triangle.v[2], color);
	drawline(data, triangle.v[2], triangle.v[0], color);
}

SDL_Surface		*new_surface(int w, int h)
{
	Uint32	color[4];

	color[0] = 0x000000ff;
	color[1] = 0x0000ff00;
	color[2] = 0x00ff0000;
	color[3] = 0xff000000;
	return (SDL_CreateRGBSurface(0, w, h, 32,
				color[0], color[1], color[2], color[3]));
}

void			putpixel(t_cube *data, int x, int y, int color)
{
	unsigned int	*pixels;

	if (x < 0 || x >= W_WIDTH
			|| y < 0 || y >= W_HEIGHT)
		return ;
	pixels = (unsigned int *)data->screen->pixels;
	pixels[x + (y * W_WIDTH)] = color;
}