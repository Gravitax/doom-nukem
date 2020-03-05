/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 21:38:18 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     get_texcoor(t_doom *data, float t, int i, int j)
{
    int     pos;
    float   u;
    float   v;
    float   w;

    if (j < 0 || i < 0 || j > W_WIDTH || i > W_HEIGHT)
        return ;
    pos = j + i * W_WIDTH;
    if (w > data->dbuffer[pos])
    {
        if (data->var.texture)
        {
            u = (1 - t) * data->fdata.su + t * data->fdata.eu;
	        v = (1 - t) * data->fdata.sv + t * data->fdata.ev;
	        w = (1 - t) * data->fdata.sw + t * data->fdata.ew;
			// u = data->fdata.simples[0] + data->fdata.simples[1];
			// v = data->fdata.simples[2] + data->fdata.simples[3];
		    // w = data->fdata.simples[4] + data->fdata.simples[5];
            putpixel(data, j, i, get_pixel(data, u / w, v / w));
            //*(int*)(&data->screen->pixels[pos]) = get_pixel(data, u / w, v / w);
        }
        else
            putpixel(data, j ,i, data->var.color);
	    data->dbuffer[pos] = w;
    }
}

static void     update_step(t_doom *data)
{
    return ;
	data->fdata.simples[0] -= data->fdata.steps[0];
	data->fdata.simples[1] += data->fdata.steps[1];
	data->fdata.simples[2] -= data->fdata.steps[2];
	data->fdata.simples[3] += data->fdata.steps[3];
	data->fdata.simples[4] -= data->fdata.steps[4];
	data->fdata.simples[5] += data->fdata.steps[5];
}

static void     precomput_step(t_doom *data, float tstep)
{
    return ;
    data->fdata.steps[0] = tstep * data->fdata.su;
	data->fdata.steps[1] = tstep * data->fdata.eu;
	data->fdata.steps[2] = tstep * data->fdata.sv;
	data->fdata.steps[3] = tstep * data->fdata.ev;
	data->fdata.steps[4] = tstep * data->fdata.sw;
	data->fdata.steps[5] = tstep * data->fdata.ew;
	data->fdata.simples[0] = data->fdata.su;
	data->fdata.simples[1] = 0;
	data->fdata.simples[2] = data->fdata.sv;
	data->fdata.simples[3] = 0;
	data->fdata.simples[4] = data->fdata.sw;
	data->fdata.simples[5] = 0;
}

static void     filltriangle(t_doom *data, int i, t_triangle triangle)
{
    int     j;
    float   t;
    float   tstep;

    if (data->fdata.ax > data->fdata.bx)
    {
        swap_floats(&data->fdata.ax, &data->fdata.bx);
        if (data->var.texture == 1)
        {
            swap_floats(&data->fdata.sv, &data->fdata.ev);
            swap_floats(&data->fdata.sw, &data->fdata.ew);
            swap_floats(&data->fdata.su, &data->fdata.eu);
        }
    }
    j = (int)(data->fdata.ax - 0.5f) - 1;
    data->fdata.bx = (int)(data->fdata.bx - 0.5f);
    t = 0;
    tstep = 1 / (data->fdata.bx - data->fdata.ax);
    precomput_step(data, tstep);
    while (++j < data->fdata.bx)
	{
        if ((i == W_HEIGHT / 2) && (j == W_WIDTH / 2))
            data->var.it = 1;
        get_texcoor(data, t, i, j);
		t += tstep;
        update_step(data);
	}
}

static void     init_step(t_doom *data)
{
    data->fdata.dax = data->fdata.x1 / (float)abs(data->fdata.y1);
    data->fdata.dbx = data->fdata.x2 / (float)abs(data->fdata.y2);
    if (data->var.texture)
    {
        data->fdata.du1 = data->fdata.u1 / (float)abs(data->fdata.y1);
        data->fdata.dv1 = data->fdata.v1 / (float)abs(data->fdata.y1);
        data->fdata.dw1 = data->fdata.w1 / (float)abs(data->fdata.y1);
        data->fdata.du2 = data->fdata.u2 / (float)abs(data->fdata.y2);
        data->fdata.dv2 = data->fdata.v2 / (float)abs(data->fdata.y2);
        data->fdata.dw2 = data->fdata.w2 / (float)abs(data->fdata.y2);
    }
}

void            fill_bottom(t_doom *data, t_triangle tmp)
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
        if (data->var.texture)
        {
            data->fdata.su = tmp.t[1].u + (i + 0.5f - tmp.v[1].y) * data->fdata.du1;
            data->fdata.sv = tmp.t[1].v + (i + 0.5f - tmp.v[1].y) * data->fdata.dv1;
            data->fdata.sw = tmp.t[1].w + (i + 0.5f - tmp.v[1].y) * data->fdata.dw1;
            data->fdata.eu = tmp.t[0].u + (i + 0.5f - tmp.v[0].y) * data->fdata.du2;
            data->fdata.ev = tmp.t[0].v + (i + 0.5f - tmp.v[0].y) * data->fdata.dv2;
            data->fdata.ew = tmp.t[0].w + (i + 0.5f - tmp.v[0].y) * data->fdata.dw2;
        }
        filltriangle(data, i, tmp);
    }
}

void            fill_top(t_doom *data, t_triangle tmp)
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
        if (data->var.texture)
        {
            data->fdata.su = tmp.t[0].u + (i + 0.5f - tmp.v[0].y) * data->fdata.du1;
            data->fdata.sv = tmp.t[0].v + (i + 0.5f - tmp.v[0].y) * data->fdata.dv1;
            data->fdata.sw = tmp.t[0].w + (i + 0.5f - tmp.v[0].y) * data->fdata.dw1;
            data->fdata.eu = tmp.t[0].u + (i + 0.5f - tmp.v[0].y) * data->fdata.du2;
            data->fdata.ev = tmp.t[0].v + (i + 0.5f - tmp.v[0].y) * data->fdata.dv2;
            data->fdata.ew = tmp.t[0].w + (i + 0.5f - tmp.v[0].y) * data->fdata.dw2;
        }
        filltriangle(data, i, tmp);
    }
}
