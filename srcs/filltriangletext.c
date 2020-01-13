/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/01/10 19:58:10 by maboye           ###   ########.fr       */
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

static void     ft2(t_cube *data, t_triangle triangle)
{
    
    int     i;
    int     j;
    t_vec3d	v0;
    t_vec3d	v1;
    t_vec3d	v2;
    t_vec2d t0;
    t_vec2d t1;
    t_vec2d t2;

    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
    t0 = triangle.t[0];
    t1 = triangle.t[1];
    t2 = triangle.t[2];  

    i = v1.y - 1;
    while (++i <= v2.y)
    {
        data->fdata.ax = v1.x + (float)(i - v1.y) * data->fdata.daxstep;
        data->fdata.bx = v0.x + (float)(i - v0.y) * data->fdata.dbxstep;
        data->fdata.texsu = t1.u + (float)(i - v1.y) * data->fdata.du1step;
        data->fdata.texsv = t1.v + (float)(i - v1.y) * data->fdata.dv1step;
        data->fdata.texsw = t1.w + (float)(i - v1.y) * data->fdata.dw1step;
        data->fdata.texeu = t0.u + (float)(i - v0.y) * data->fdata.du2step;
        data->fdata.texev = t0.v + (float)(i - v0.y) * data->fdata.dv2step;
        data->fdata.texew = t0.w + (float)(i - v0.y) * data->fdata.dw2step;
        if (data->fdata.ax > data->fdata.bx)
            fillswap(data);
        data->fdata.texu = data->fdata.texsu;
        data->fdata.texv = data->fdata.texsv;
        data->fdata.texw = data->fdata.texsw;
        float   tstep = 1 / ((float)(data->fdata.bx - data->fdata.ax));
        float   t = 0;
        j = data->fdata.ax - 1;
    	while (++j < data->fdata.bx)
		{
			data->fdata.texu = (1.0f - t) * data->fdata.texsu + t * data->fdata.texeu;
			data->fdata.texv = (1.0f - t) * data->fdata.texsv + t * data->fdata.texev;
			data->fdata.texw = (1.0f - t) * data->fdata.texsw + t * data->fdata.texew;
			// if (data->fdata.texw > data->dbuffer[i * W_WIDTH + j])
			// {
                putpixel(data, j, i, triangle.color);
				//data->dbuffer[i * W_WIDTH + j] = data->fdata.texw;
			// }
			t += tstep;
		}
    }
}

static void     ft1(t_cube *data, t_triangle triangle)
{
    int     i;
    int     j;
    t_vec3d	v0;
    t_vec3d	v1;
    t_vec3d	v2;
    t_vec2d t0;
    t_vec2d t1;
    t_vec2d t2;

    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
    t0 = triangle.t[0];
    t1 = triangle.t[1];
    t2 = triangle.t[2];

    i = v0.y - 1;
    while (++i <= v1.y)
    {
        data->fdata.ax = v0.x + (float)(i - v0.y) * data->fdata.daxstep;
        data->fdata.bx = v0.x + (float)(i - v0.y) * data->fdata.dbxstep;
        data->fdata.texsu = t0.u + (float)(i - v0.y) * data->fdata.du1step;
        data->fdata.texsv = t0.v + (float)(i - v0.y) * data->fdata.dv1step;
        data->fdata.texsw = t0.w + (float)(i - v0.y) * data->fdata.dw1step;
        data->fdata.texeu = t0.u + (float)(i - v0.y) * data->fdata.du2step;
        data->fdata.texev = t0.v + (float)(i - v0.y) * data->fdata.dv2step;
        data->fdata.texew = t0.w + (float)(i - v0.y) * data->fdata.dw2step;
        if (data->fdata.ax > data->fdata.bx)
            fillswap(data);
        data->fdata.texu = data->fdata.texsu;
        data->fdata.texv = data->fdata.texsv;
        data->fdata.texw = data->fdata.texsw;
        float   tstep = 1 / ((float)(data->fdata.bx - data->fdata.ax));
        float   t = 0;
        j = data->fdata.ax - 1;
    	while (++j < data->fdata.bx)
		{
			data->fdata.texu = (1.0f - t) * data->fdata.texsu + t * data->fdata.texeu;
			data->fdata.texv = (1.0f - t) * data->fdata.texsv + t * data->fdata.texev;
			data->fdata.texw = (1.0f - t) * data->fdata.texsw + t * data->fdata.texew;
			// if (data->fdata.texw > data->dbuffer[i * W_WIDTH + j])
			// {
                putpixel(data, j, i, triangle.color);
				//data->dbuffer[i * W_WIDTH + j] = data->fdata.texw;
			// }
			t += tstep;
		}
    }
}

void			filltriangletext(t_cube *data, t_triangle triangle, int color)
{
    t_vec3d	v0;
    t_vec3d	v1;
    t_vec3d	v2;
    t_vec2d t0;
    t_vec2d t1;
    t_vec2d t2;

    ft_memset((void *)&data->fdata, 0, sizeof(t_fdata));
    v0 = triangle.v[0];
    v1 = triangle.v[1];
    v2 = triangle.v[2];
    t0 = triangle.t[0];
    t1 = triangle.t[1];
    t2 = triangle.t[2];
    if (v1.y < v0.y)
    {
        ft_swap((void *)&v1, (void *)&v0);
        ft_swap((void *)&t1, (void *)&t0);
    }
    if (v2.y < v0.y)
    {
        ft_swap((void *)&v2, (void *)&v0);
        ft_swap((void *)&t2, (void *)&t0);
    }
    if (v2.y < v1.y)
    {
        ft_swap((void *)&v2, (void *)&v1);
        ft_swap((void *)&t2, (void *)&t1);
    }
    data->fdata.du1 = t1.u - t0.u;
    data->fdata.dv1 = t1.v - t0.v;
    data->fdata.dw1 = t1.w - t0.w;
    data->fdata.dx1 = v1.x - v0.x;
    data->fdata.dy1 = v1.y - v0.y;

    data->fdata.du2 = t2.u - t0.u;
    data->fdata.dv2 = t2.v - t0.v;
    data->fdata.dw2 = t2.w - t0.w;
    data->fdata.dx2 = v2.x - v0.x;
    data->fdata.dy2 = v2.y - v0.y;
	if (data->fdata.dy2)
    {
        data->fdata.dbxstep = data->fdata.dx2 / (float)abs(data->fdata.dy2);
        data->fdata.du2step = data->fdata.du2 / (float)abs(data->fdata.dy2);
        data->fdata.dv2step = data->fdata.dv2 / (float)abs(data->fdata.dy2);
        data->fdata.dw2step = data->fdata.dw2 / (float)abs(data->fdata.dy2);
    }
	if (data->fdata.dy1)
    {
        data->fdata.daxstep = data->fdata.dx1 / (float)abs(data->fdata.dy1);
        data->fdata.du1step = data->fdata.du1 / (float)abs(data->fdata.dy1);
        data->fdata.dv1step = data->fdata.dv1 / (float)abs(data->fdata.dy1);
        data->fdata.dw1step = data->fdata.dw1 / (float)abs(data->fdata.dy1);
        ft1(data, (t_triangle){ v0, v1, v2, t0, t1, t2, color });
    }
    data->fdata.du1 = t2.u - t1.u;
    data->fdata.dv1 = t2.v - t1.v;
    data->fdata.dw1 = t2.w - t1.w;
    data->fdata.dx1 = v2.x - v1.x;
    data->fdata.dy1 = v2.y - v1.y;
	if (data->fdata.dy2)
        data->fdata.dbxstep = data->fdata.dx2 / (float)abs(data->fdata.dy2);
	data->fdata.du1step = 0, data->fdata.dv1step = 0;
	if (data->fdata.dy1)
    {
        data->fdata.daxstep = data->fdata.dx1 / (float)abs(data->fdata.dy1);
        data->fdata.du1step = data->fdata.du1 / (float)abs(data->fdata.dy1);
        data->fdata.dv1step = data->fdata.dv1 / (float)abs(data->fdata.dy1);
        data->fdata.dw1step = data->fdata.dw1 / (float)abs(data->fdata.dy1);
        ft2(data, (t_triangle){ v0, v1, v2, t0, t1, t2, color });
    }
}
