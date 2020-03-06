/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 21:28:46 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void			clipping(t_doom *data, t_triangle ttrans)
{
	int			i;
	int			clippedtriangle;

	data->cdata.nplane = (t_vec3d){ 0, 0, 0.1f, 1 };
	data->cdata.pplane = (t_vec3d){ 0, 0, 1, 1 };
	data->cdata.in = mmvtriangle(data->matrix.view, ttrans);
	clippedtriangle = cliptriangle(data);
	i = -1;
	while (++i < clippedtriangle)
		rasterisation(data, mmvtriangle(data->matrix.proj, data->cdata.out[i]));
}

static int			to_draw(t_doom *data, t_triangle *triangle, int i, int j)
{
	int		nb;
	t_vec3d	camray;
	t_vec3d	n;

	n = veccrossproduct(vecsub(triangle->v[1], triangle->v[0]),
						vecsub(triangle->v[2], triangle->v[0]));
	n = vecnormalise(n);
	camray = vecsub(triangle->v[0], data->vector.camera);
	nb = 255 * vecdotproduct(vecnormalise(data->vector.lightdir), n);
	if (nb < 0)
		nb = 0;
	if (data->var.is == i && data->var.io == j)
		triangle->color = 0xff00ffff;
	else
		triangle->color = (nb | nb << 8 | nb << 16 | 255 << 24);
	return (vecdotproduct(n, vecnormalise(camray)) < 0);
}

static void			display_object(t_doom *data, t_obj object)
{
	int			j;
	t_triangle	ttrans;

	data->var.it = 0;
	j = -1;
	while (++j < object.size)
	{
		data->var.texture = object.texture;
		ttrans = mmvtriangle(data->matrix.world, object.mesh[j]);
		if (to_draw(data, &ttrans, object.si, object.i) == 1)
			clipping(data, ttrans);
		if (data->var.it == 1)
		{
			data->var.is = object.si;
			data->var.io = object.i;
		}
	}
}

void				display_mesh(t_doom *data)
{
	int			i;
	int			j;

	i = -1;
	while (++i < data->var.ac - 1)
	{
		data->texture = data->scene[i].texture;
		j = -1;
		while (++j < data->scene[i].iobj)
			display_object(data, data->scene[i].object[j]);
	}
}

static void			load_world(t_doom *data)
{
	t_mat		camrot;

	data->vector.right = (t_vec3d){ 1, 0, 0, 1 };
	data->vector.target = (t_vec3d){ 0, 0, 1, 1 };
	data->vector.up = (t_vec3d){ 0, 1, 0, 1 };
	data->matrix.world = mat_mulmatrix(data->matrix.rotx, data->matrix.roty);
	data->matrix.world = mat_mulmatrix(data->matrix.world, data->matrix.rotz);
	data->matrix.world = mat_mulmatrix(data->matrix.world, data->matrix.trans);
	camrot = mat_mulmatrix(data->matrix.camrotx, data->matrix.camroty);
	data->vector.lookdir = mat_mulvector(camrot, data->vector.target);
	data->vector.target = vecadd(data->vector.camera, data->vector.lookdir);
	pointatmatrix(&data->matrix.pointat, data->vector.camera,
		data->vector.target, data->vector.up);
	quickinversematrix(&data->matrix.view, data->matrix.pointat);
	data->vector.right = mat_mulvector(camrot, data->vector.right);
	data->vector.up = mat_mulvector(camrot, data->vector.up);
}

void				display_renderer(t_doom *data)
{
	int				i;
	unsigned int	*pixels;
	SDL_Rect		rect;

	rect = (SDL_Rect){ 0, 0, W_WIDTH, W_HEIGHT };
	data->window = SDL_CreateTextureFromSurface(data->renderer, data->screen);
	pixels = (unsigned int *)data->screen->pixels;
	while (++i < W_LEN)
		pixels[i] = (0 | 0 << 8 | 0 << 16 | 255 << 24);
	SDL_RenderCopy(data->renderer, data->window, NULL, &rect);
	SDL_DestroyTexture(data->window);
	SDL_RenderPresent(data->renderer);
}

void				display(t_doom *data)
{
	int				i;

	i = -1;
	while (++i < W_LEN)
		data->dbuffer[i] = 0;
	load_world(data);
	display_mesh(data);
	display_renderer(data);
}
