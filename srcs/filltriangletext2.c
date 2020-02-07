/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/07 06:26:31 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     filltriangle(t_cube *data, t_triangle triangle, int i)
{
    int     j;
    float   t;
    float   tstep;

    if (data->fdata.ax > data->fdata.bx)
    {
        swap_floats(&data->fdata.ax, &data->fdata.bx);
        swap_floats(&data->fdata.texsu, &data->fdata.texeu);
        swap_floats(&data->fdata.texsv, &data->fdata.texev);
        swap_floats(&data->fdata.texsw, &data->fdata.texew);
    }
    j = (int)(data->fdata.ax - 0.5f) - 1;
    data->fdata.bx = (int)(data->fdata.bx - 0.5f);
    t = 0;
    tstep = 1 / (data->fdata.bx - data->fdata.ax);
    while (++j < data->fdata.bx)
	{
		data->fdata.texu = (1 - t) * data->fdata.texsu + t * data->fdata.texeu;
		data->fdata.texv = (1 - t) * data->fdata.texsv + t * data->fdata.texev;
		data->fdata.texw = (1 - t) * data->fdata.texsw + t * data->fdata.texew;
        //printf("u: %f, v: %f\n",data->fdata.texu, data->fdata.texv);
        putpixel(data, j, i, //triangle.color);
            get_pixel(data,
                data->fdata.texu,
                data->fdata.texv));
		t += tstep;
	}
}

static void     init_step(t_cube *data)
{
    data->fdata.daxstep = data->fdata.dx1 / (float)abs(data->fdata.dy1);
    data->fdata.dbxstep = data->fdata.dx2 / (float)abs(data->fdata.dy2);
    data->fdata.du1step = data->fdata.du1 / (float)abs(data->fdata.dy1);
    data->fdata.dv1step = data->fdata.dv1 / (float)abs(data->fdata.dy1);
    data->fdata.dw1step = data->fdata.dw1 / (float)abs(data->fdata.dy1);
    data->fdata.du2step = data->fdata.du2 / (float)abs(data->fdata.dy2);
    data->fdata.dv2step = data->fdata.dv2 / (float)abs(data->fdata.dy2);
    data->fdata.dw2step = data->fdata.dw2 / (float)abs(data->fdata.dy2);
}

void            fill_bottom(t_cube *data, t_triangle triangle)
{
    int     i;
    int     end;

    init_step(data);
    i = (int)ceil(triangle.v[1].y - 0.5f) - 1;
    end = (int)ceil(triangle.v[2].y - 0.5f);
    while (++i < end)
    {
        data->fdata.ax = triangle.v[1].x + (i + 0.5f - triangle.v[1].y) * data->fdata.daxstep;
        data->fdata.bx = triangle.v[0].x + (i + 0.5f - triangle.v[0].y) * data->fdata.dbxstep;
        data->fdata.texsu = triangle.t[1].u + (i + 0.5f - triangle.v[1].y) * data->fdata.du1step;
        data->fdata.texsv = triangle.t[1].v + (i + 0.5f - triangle.v[1].y) * data->fdata.dv1step;
        data->fdata.texsw = triangle.t[1].w + (i + 0.5f - triangle.v[1].y) * data->fdata.dw1step;
        data->fdata.texeu = triangle.t[0].u + (i + 0.5f - triangle.v[0].y) * data->fdata.du2step;
        data->fdata.texev = triangle.t[0].v + (i + 0.5f - triangle.v[0].y) * data->fdata.dv2step;
        data->fdata.texew = triangle.t[0].w + (i + 0.5f - triangle.v[0].y) * data->fdata.dw2step;
        filltriangle(data, triangle, i);
    }
}

void            fill_top(t_cube *data, t_triangle triangle)
{
    int     i;
    int     end;

    init_step(data);
    i = (int)ceil(triangle.v[0].y - 0.5f) - 1;
    end = (int)ceil(triangle.v[1].y - 0.5f);
    while (++i < end)
    {
        data->fdata.ax = triangle.v[0].x + (i + 0.5f - triangle.v[0].y) * data->fdata.daxstep;
        data->fdata.bx = triangle.v[0].x + (i + 0.5f - triangle.v[0].y) * data->fdata.dbxstep;
        data->fdata.texsu = triangle.t[0].u + (i + 0.5f - triangle.v[0].y) * data->fdata.du1step;
        data->fdata.texsv = triangle.t[0].v + (i + 0.5f - triangle.v[0].y) * data->fdata.dv1step;
        data->fdata.texsw = triangle.t[0].w + (i + 0.5f - triangle.v[0].y) * data->fdata.dw1step;
        data->fdata.texeu = triangle.t[0].u + (i + 0.5f - triangle.v[0].y) * data->fdata.du2step;
        data->fdata.texev = triangle.t[0].v + (i + 0.5f - triangle.v[0].y) * data->fdata.dv2step;
        data->fdata.texew = triangle.t[0].w + (i + 0.5f - triangle.v[0].y) * data->fdata.dw2step;
        filltriangle(data, triangle, i);
    }
}
