/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/01/29 19:28:19 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     fillswap(t_cube *data)
{
    float   tmp;

    tmp = data->fdata.ax;
    data->fdata.ax = data->fdata.bx;
    data->fdata.bx = tmp;

    tmp = data->fdata.texsu;
    data->fdata.texsu = data->fdata.texeu;
    data->fdata.texeu = tmp;

    tmp = data->fdata.texsv;
    data->fdata.texsv = data->fdata.texev;
    data->fdata.texev = tmp;

    tmp = data->fdata.texsw;
    data->fdata.texsw = data->fdata.texew;
    data->fdata.texew = tmp;
}

static void     filltriangle(t_cube *data, t_triangle triangle, int i)
{
    int     j;
    int     pos;
    float   t;
    float   tstep;

    data->fdata.texu = data->fdata.texsu;
    data->fdata.texv = data->fdata.texsv;
    data->fdata.texw = data->fdata.texsw;
    j = data->fdata.ax - 1;
    t = 0;
    tstep = 1 / ((float)(data->fdata.bx - data->fdata.ax));
    while (++j < data->fdata.bx)
	{
		data->fdata.texu = (1 - t) * data->fdata.texsu + t * data->fdata.texeu;
		data->fdata.texv = (1 - t) * data->fdata.texsv + t * data->fdata.texev;
		data->fdata.texw = (1 - t) * data->fdata.texsw + t * data->fdata.texew;
        pos = i * W_WIDTH + j;
        // if (pos < W_WIDTH * W_HEIGHT && pos > -1)
        // {
	    //     if (data->fdata.texw >= data->dbuffer[pos])
		//     {
                putpixel(data, j, i, triangle.color);
		        // data->dbuffer[pos] = data->fdata.texw;
		//     }
        // }
		t += tstep;
	}
}

static void     init_step(t_cube *data)
{
    data->fdata.du1step = data->fdata.du1 / (float)abs(data->fdata.dy1);
    data->fdata.dv1step = data->fdata.dv1 / (float)abs(data->fdata.dy1);
    data->fdata.dw1step = data->fdata.dw1 / (float)abs(data->fdata.dy1);
    data->fdata.daxstep = data->fdata.dx1 / (float)abs(data->fdata.dy1);
}

static void     fill_bottom(t_cube *data, t_triangle triangle)
{
    int     i;
    int     j; 

    init_step(data);
    i = triangle.v[1].y - 1;
    while (++i <= triangle.v[2].y)
    {
        data->fdata.ax = triangle.v[1].x + (float)(i - triangle.v[1].y) * data->fdata.daxstep;
        data->fdata.bx = triangle.v[0].x + (float)(i - triangle.v[0].y) * data->fdata.dbxstep;
        data->fdata.texsu = triangle.t[1].u + (float)(i - triangle.v[1].y) * data->fdata.du1step;
        data->fdata.texsv = triangle.t[1].v + (float)(i - triangle.v[1].y) * data->fdata.dv1step;
        data->fdata.texsw = triangle.t[1].w + (float)(i - triangle.v[1].y) * data->fdata.dw1step;
        data->fdata.texeu = triangle.t[0].u + (float)(i - triangle.v[0].y) * data->fdata.du2step;
        data->fdata.texev = triangle.t[0].v + (float)(i - triangle.v[0].y) * data->fdata.dv2step;
        data->fdata.texew = triangle.t[0].w + (float)(i - triangle.v[0].y) * data->fdata.dw2step;
        if (data->fdata.ax > data->fdata.bx)
            fillswap(data);
        filltriangle(data, triangle, i);
    }
}

static void     fill_top(t_cube *data, t_triangle triangle)
{
    int     i;
    int     j;

    init_step(data);
    i = triangle.v[0].y - 1;
    while (++i <= triangle.v[1].y)
    {
        data->fdata.ax = triangle.v[0].x + (float)(i - triangle.v[0].y) * data->fdata.daxstep;
        data->fdata.bx = triangle.v[0].x + (float)(i - triangle.v[0].y) * data->fdata.dbxstep;
        data->fdata.texsu = triangle.t[0].u + (float)(i - triangle.v[0].y) * data->fdata.du1step;
        data->fdata.texsv = triangle.t[0].v + (float)(i - triangle.v[0].y) * data->fdata.dv1step;
        data->fdata.texsw = triangle.t[0].w + (float)(i - triangle.v[0].y) * data->fdata.dw1step;
        data->fdata.texeu = triangle.t[0].u + (float)(i - triangle.v[0].y) * data->fdata.du2step;
        data->fdata.texev = triangle.t[0].v + (float)(i - triangle.v[0].y) * data->fdata.dv2step;
        data->fdata.texew = triangle.t[0].w + (float)(i - triangle.v[0].y) * data->fdata.dw2step;
        if (data->fdata.ax > data->fdata.bx)
            fillswap(data);
        filltriangle(data, triangle, i);
    }
}

static void     init_filldata(t_cube *data, t_triangle tmp)
{
    data->fdata.du1 = tmp.t[1].u - tmp.t[0].u;
    data->fdata.dv1 = tmp.t[1].v - tmp.t[0].v;
    data->fdata.dw1 = tmp.t[1].w - tmp.t[0].w;
    data->fdata.dx1 = tmp.v[1].x - tmp.v[0].x;
    data->fdata.dy1 = tmp.v[1].y - tmp.v[0].y;
    data->fdata.du2step = 0;
    data->fdata.dv2step = 0;
    data->fdata.dw2step = 0;
    data->fdata.dbxstep = 0;
    data->fdata.du2 = tmp.t[2].u - tmp.t[0].u;
    data->fdata.dv2 = tmp.t[2].v - tmp.t[0].v;
    data->fdata.dw2 = tmp.t[2].w - tmp.t[0].w;
    data->fdata.dx2 = tmp.v[2].x - tmp.v[0].x;
    data->fdata.dy2 = tmp.v[2].y - tmp.v[0].y;
	if (data->fdata.dy2)
    {
        data->fdata.du2step = data->fdata.du2 / (float)abs(data->fdata.dy2);
        data->fdata.dv2step = data->fdata.dv2 / (float)abs(data->fdata.dy2);
        data->fdata.dw2step = data->fdata.dw2 / (float)abs(data->fdata.dy2);
        data->fdata.dbxstep = data->fdata.dx2 / (float)abs(data->fdata.dy2);
    }
}

void			filltriangletext(t_cube *data, t_triangle triangle)
{
    t_triangle  tmp;

    tmp = triangle;
    if (tmp.v[1].y < tmp.v[0].y)
        ft_swap((void *)&tmp.v[1], (void *)&tmp.v[0]);
    if (tmp.v[2].y < tmp.v[0].y)
        ft_swap((void *)&tmp.v[2], (void *)&tmp.v[0]);
    if (tmp.v[2].y < tmp.v[1].y)
        ft_swap((void *)&tmp.v[2], (void *)&tmp.v[1]);
    init_filldata(data, tmp);
	if (data->fdata.dy1)
        fill_top(data, tmp);
    data->fdata.du1 = tmp.t[2].u - tmp.t[1].u;
    data->fdata.dv1 = tmp.t[2].v - tmp.t[1].v;
    data->fdata.dw1 = tmp.t[2].w - tmp.t[1].w;
    data->fdata.dx1 = tmp.v[2].x - tmp.v[1].x;
    data->fdata.dy1 = tmp.v[2].y - tmp.v[1].y;
	if (data->fdata.dy1)
        fill_bottom(data, tmp);
}
