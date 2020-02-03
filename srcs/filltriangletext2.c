/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext2.c                                :+:      :+:    :+:   */
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
    float   t;
    float   tstep;

    j = data->fdata.ax - 1;
    t = 0;
    tstep = 1 / ((float)(data->fdata.bx - data->fdata.ax));
    while (++j < data->fdata.bx)
	{
		data->fdata.texu = (1 - t) * data->fdata.texsu + t * data->fdata.texeu;
		data->fdata.texv = (1 - t) * data->fdata.texsv + t * data->fdata.texev;
		data->fdata.texw = (1 - t) * data->fdata.texsw + t * data->fdata.texew;
        putpixel(data, j, i,// triangle.color);
            get_pixel(data, data->fdata.texu, data->fdata.texv));
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

void            fill_bottom(t_cube *data, t_triangle triangle)
{
    int     i;

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

void            fill_top(t_cube *data, t_triangle triangle)
{
    int     i;

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
