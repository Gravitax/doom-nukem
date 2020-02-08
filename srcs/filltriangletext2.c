/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/08 01:20:52 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     get_texcoor(t_cube *data, float t, int i, int j)
{
    int     pos;
    float   u;
    float   v;
    float   w;

	u = (1 - t) * data->fdata.su + t * data->fdata.eu;
	v = (1 - t) * data->fdata.sv + t * data->fdata.ev;
	w = (1 - t) * data->fdata.sw + t * data->fdata.ew;
    pos = j + i * W_WIDTH;
    if (w > data->dbuffer[pos])
	{
        putpixel(data, j, i,
            //data->var.color);
            get_pixel(data, u / w, v / w));
	    data->dbuffer[pos] = w;
    }    
}

static void     filltriangle(t_cube *data, int i)
{
    int     j;
    float   t;
    float   tstep;

    if (data->fdata.ax > data->fdata.bx)
    {
        swap_floats(&data->fdata.ax, &data->fdata.bx);
        swap_floats(&data->fdata.su, &data->fdata.eu);
        swap_floats(&data->fdata.sv, &data->fdata.ev);
        swap_floats(&data->fdata.sw, &data->fdata.ew);
    }
    j = (int)(data->fdata.ax - 0.5f) - 1;
    data->fdata.bx = (int)(data->fdata.bx - 0.5f);
    t = 0;
    tstep = 1 / (data->fdata.bx - data->fdata.ax);
    while (++j < data->fdata.bx)
	{
        get_texcoor(data, t, i, j);
		t += tstep;
	}
}

static void     init_step(t_cube *data)
{
    data->fdata.dax = data->fdata.x1 / (float)abs(data->fdata.y1);
    data->fdata.dbx = data->fdata.x2 / (float)abs(data->fdata.y2);
    data->fdata.du1 = data->fdata.u1 / (float)abs(data->fdata.y1);
    data->fdata.dv1 = data->fdata.v1 / (float)abs(data->fdata.y1);
    data->fdata.dw1 = data->fdata.w1 / (float)abs(data->fdata.y1);
    data->fdata.du2 = data->fdata.u2 / (float)abs(data->fdata.y2);
    data->fdata.dv2 = data->fdata.v2 / (float)abs(data->fdata.y2);
    data->fdata.dw2 = data->fdata.w2 / (float)abs(data->fdata.y2);
}

void            fill_bottom(t_cube *data, t_triangle tmp)
{
    int     i;
    int     end;

    init_step(data);
    i = (int)ceil(tmp.v[1].y - 0.5f) - 1;
    end = (int)ceil(tmp.v[2].y - 0.5f);
    while (++i < end)
    {
        data->fdata.ax = tmp.v[1].x + (i + 0.5f - tmp.v[1].y) * data->fdata.dax;
        data->fdata.bx = tmp.v[0].x + (i + 0.5f - tmp.v[0].y) * data->fdata.dbx;
        data->fdata.su = tmp.t[1].u + (i + 0.5f - tmp.v[1].y) * data->fdata.du1;
        data->fdata.sv = tmp.t[1].v + (i + 0.5f - tmp.v[1].y) * data->fdata.dv1;
        data->fdata.sw = tmp.t[1].w + (i + 0.5f - tmp.v[1].y) * data->fdata.dw1;
        data->fdata.eu = tmp.t[0].u + (i + 0.5f - tmp.v[0].y) * data->fdata.du2;
        data->fdata.ev = tmp.t[0].v + (i + 0.5f - tmp.v[0].y) * data->fdata.dv2;
        data->fdata.ew = tmp.t[0].w + (i + 0.5f - tmp.v[0].y) * data->fdata.dw2;
        filltriangle(data, i);
    }
}

void            fill_top(t_cube *data, t_triangle tmp)
{
    int     i;
    int     end;

    init_step(data);
    i = (int)ceil(tmp.v[0].y - 0.5f) - 1;
    end = (int)ceil(tmp.v[1].y - 0.5f);
    while (++i < end)
    {
        data->fdata.ax = tmp.v[0].x + (i + 0.5f - tmp.v[0].y) * data->fdata.dax;
        data->fdata.bx = tmp.v[0].x + (i + 0.5f - tmp.v[0].y) * data->fdata.dbx;
        data->fdata.su = tmp.t[0].u + (i + 0.5f - tmp.v[0].y) * data->fdata.du1;
        data->fdata.sv = tmp.t[0].v + (i + 0.5f - tmp.v[0].y) * data->fdata.dv1;
        data->fdata.sw = tmp.t[0].w + (i + 0.5f - tmp.v[0].y) * data->fdata.dw1;
        data->fdata.eu = tmp.t[0].u + (i + 0.5f - tmp.v[0].y) * data->fdata.du2;
        data->fdata.ev = tmp.t[0].v + (i + 0.5f - tmp.v[0].y) * data->fdata.dv2;
        data->fdata.ew = tmp.t[0].w + (i + 0.5f - tmp.v[0].y) * data->fdata.dw2;
        filltriangle(data, i);
    }
}
