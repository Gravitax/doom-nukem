/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/01/10 16:35:38 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void			triangletransform(t_cube *data, t_triangle *triangle)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		// triangle->t[i].u = triangle->t[i].u / triangle->v[i].w;
		// triangle->t[i].v = triangle->t[i].v / triangle->v[i].w;
		triangle->v[i].w = (1 / triangle->v[i].w);
		triangle->v[i] = vecmul(triangle->v[i], data->zoom * triangle->v[i].w);
		triangle->v[i] = vecadd(triangle->v[i], data->vector.offset);
		triangle->v[i].x *= data->xfactor;
		triangle->v[i].y *= data->yfactor;
	}
}

static t_triangle	mmvtriangle(t_mat matrix, t_triangle triangle)
{
	t_triangle	tresult;

	tresult.v[0] = mat_mulvector(matrix, triangle.v[0]);
	tresult.v[1] = mat_mulvector(matrix, triangle.v[1]);
	tresult.v[2] = mat_mulvector(matrix, triangle.v[2]);
	return (tresult);
}

static void			projection(t_cube *data, t_triangle ttrans)
{
	int			i;
	int			clippedtriangle;
	t_triangle	tproj;
	t_triangle	tview;
	t_triangle	buffer[10];

	tview = mmvtriangle(data->matrix.view, ttrans);
	tview.color = ttrans.color;
	data->cdata.nplane = (t_vec3d){ 0, 0, 0.1f, 1 };
	data->cdata.pplane = (t_vec3d){ 0, 0, 1, 1 };
	data->cdata.in = tview;
	clippedtriangle = cliptriangle(data);
	i = -1;
	while (++i < clippedtriangle)
	{
		tproj = mmvtriangle(data->matrix.proj,  data->cdata.out[i]);
		tproj.color = data->cdata.out[i].color;
		tproj.t[0] = data->cdata.out[i].t[0];
		tproj.t[1] = data->cdata.out[i].t[1];
		tproj.t[2] = data->cdata.out[i].t[2];
		triangletransform(data, &tproj);
		buffer[i] =  tproj;
	}
	while (i--)
		clipping(data, &buffer[i]);
}

static int			to_draw(t_cube *data, t_triangle *triangle)
{
	int		nb;
	float	dp;
	t_vec3d	camray;
	t_vec3d	n;

	n = veccrossproduct(vecsub(triangle->v[1], triangle->v[0]),
						vecsub(triangle->v[2], triangle->v[0]));
	n = vecnormalise(n);
	camray = vecsub(triangle->v[0], data->vector.camera);
	dp = vecdotproduct(vecnormalise(data->vector.lightdir), n);
	nb = 255 * dp;
	if (nb < 0)
		nb = 0;
	triangle->color = (nb | nb << 8 | nb << 16 | 255 << 24);
	return (vecdotproduct(n, camray) < 0);
}

static void			display_mesh(t_cube *data)
{
	int			i;
	int			j;
	t_triangle	ttrans;

	i = -1;
	while (++i < data->ac - 1)
	{
		j = data->mesh[i].size + 1;
		while (j--)
		{
			ttrans = mmvtriangle(data->matrix.world, data->mesh[i].object[j]);
			if (to_draw(data, &ttrans) == 1)
				projection(data, ttrans);
		}
	}
}

static void			cube3d(t_cube *data)
{
	t_mat		camrot;

	data->matrix.world = mat_mulmatrix(data->matrix.rotx, data->matrix.roty);
	data->matrix.world = mat_mulmatrix(data->matrix.world, data->matrix.rotz);
	data->matrix.world = mat_mulmatrix(data->matrix.world, data->matrix.trans);
	data->vector.target = (t_vec3d){ 0, 0, 1, 1 };
	data->vector.right = (t_vec3d){ 1, 0, 0, 1 };
	data->vector.up = (t_vec3d){ 0, 1, 0, 1 };
	camrot = mat_mulmatrix(data->matrix.camroty, data->matrix.camrotx);
	data->vector.lookdir = mat_mulvector(camrot, data->vector.target);
	data->vector.right = mat_mulvector(camrot, data->vector.right);
	data->vector.target = vecadd(data->vector.camera, data->vector.lookdir);
	pointatmatrix(&data->matrix.pointat, data->vector.camera,
		data->vector.target, data->vector.up);
	quickinversematrix(&data->matrix.view, data->matrix.pointat);
	data->vector.up = mat_mulvector(camrot, data->vector.up);
	display_mesh(data);
}

void				display(t_cube *data)
{
	int				i;
	unsigned int	*pixels;
	SDL_Rect		rect;

	i = -1;
	while (++i < W_LEN)
		data->dbuffer[i] = 0;
	cube3d(data);
	rect.h = W_HEIGHT;
	rect.w = W_WIDTH;
	rect.x = 0;
	rect.y = 0;
	data->window = SDL_CreateTextureFromSurface(data->renderer, data->screen);
	pixels = (unsigned int *)data->screen->pixels;
	while (i--)
		pixels[i] = (0 | 0 << 8 | 0 << 16 | 255 << 24);
	SDL_RenderCopy(data->renderer, data->window, NULL, &rect);
	SDL_DestroyTexture(data->window);
	SDL_RenderPresent(data->renderer);
}
