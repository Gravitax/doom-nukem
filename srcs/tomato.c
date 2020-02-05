/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/01/16 19:30:19 by bebosson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static t_vec2d      texcoord(t_vec2d v1, t_vec2d v2, float k)
{
    return ((t_vec2d){ (v1.u + v2.u) * k, (v1.v + v2.v) * k });
}

static t_vec2d      texstep(t_vec2d v1, t_vec2d v2, float k)
{
    return ((t_vec2d){ (v1.u - v2.u) / k, (v1.v - v2.v) / k });
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

static void     filltriangle(t_cube *data, t_triangle triangle, int y)
{
    int     x;
    float   t;
    float   tstep;

    x = (int)ceil(data->fdata.ax - 0.5f) - 1;
    data->fdata.bx = (int)ceil(data->fdata.bx - 0.5f);
    t = 0;
    tstep = 1 / (data->fdata.bx - data->fdata.ax);

    //t_vec2d scanstep = texstep(data->fdata.right, data->fdata.left, data->fdata.bx - data->fdata.ax);
    //data->fdata.tc = texcoord(data->fdata.left, scanstep, (float)x + 0.5f - data->fdata.bx);
    while (++x < data->fdata.bx)
	{
        //data->fdata.tc = texcoord(data->fdata.tc, scanstep, 1);
		data->fdata.texu = (1 - t) * data->fdata.texsu + t * data->fdata.texeu;
		data->fdata.texv = (1 - t) * data->fdata.texsv + t * data->fdata.texev;
		data->fdata.texw = (1 - t) * data->fdata.texsw + t * data->fdata.texew;
        //printf("u: %f, v: %f\n", data->fdata.tc.u, data->fdata.tc.v);
        putpixel(data, x, y, //triangle.color);
            get_pixel(data, //data->fdata.tc.u, data->fdata.tc.v));
                data->fdata.texu,
                data->fdata.texv));
		t += tstep;
	}
}

static void			flatbot(t_cube *data, t_triangle tmp)
{
    int     y;
    int     end;

	y = (int)ceil(tmp.v[0].y - 0.5f) - 1;
    end = (int)ceil(tmp.v[2].y - 0.5f);
    //data->fdata.left = tmp.t[0];
    // data->fdata.right = tmp.t[0];
    // data->fdata.bot = tmp.t[1];

    // data->fdata.stepl = texstep(data->fdata.bot, data->fdata.left, tmp.v[2].y - tmp.v[0].y);
    // data->fdata.stepr = texstep(data->fdata.bot, data->fdata.right, tmp.v[2].y - tmp.v[1].y);
    // data->fdata.left = texcoord(data->fdata.left, data->fdata.stepl, (float)y + 0.5f + 1 - tmp.v[1].y);
    // data->fdata.right = texcoord(data->fdata.right, data->fdata.stepr, (float)y + 0.5f + 1 - tmp.v[1].y);

    data->fdata.du1 = tmp.t[1].u - tmp.t[0].u;
    data->fdata.dv1 = tmp.t[1].v - tmp.t[0].v;
    data->fdata.dw1 = tmp.t[1].w - tmp.t[0].w;
    data->fdata.dx1 = tmp.v[1].x - tmp.v[0].x;
    data->fdata.dy1 = tmp.v[1].y - tmp.v[0].y;
    data->fdata.du2 = tmp.t[2].u - tmp.t[0].u;
    data->fdata.dv2 = tmp.t[2].v - tmp.t[0].v;
    data->fdata.dw2 = tmp.t[2].w - tmp.t[0].w;
    data->fdata.dx2 = tmp.v[2].x - tmp.v[0].x;
    data->fdata.dy2 = tmp.v[2].y - tmp.v[0].y;
    init_step(data);
	// data->fdata.daxstep = (tmp.v[1].x - tmp.v[0].x) / (float)(tmp.v[1].y - tmp.v[0].y);
    // data->fdata.dbxstep = (tmp.v[2].x - tmp.v[0].x) / (float)(tmp.v[2].y - tmp.v[0].y);
    while (++y < end)
    {
        // data->fdata.left = texcoord(data->fdata.left, data->fdata.stepl, 1);
        // data->fdata.right = texcoord(data->fdata.right, data->fdata.stepr, 1);
        data->fdata.ax = tmp.v[0].x + (y + 0.5f - tmp.v[0].y) * data->fdata.daxstep;
        data->fdata.bx = tmp.v[0].x + (y + 0.5f - tmp.v[0].y) * data->fdata.dbxstep;
        data->fdata.texsu = tmp.t[0].u + (y + 0.5f - tmp.v[0].y) * data->fdata.du1step;
        data->fdata.texsv = tmp.t[0].v + (y + 0.5f - tmp.v[0].y) * data->fdata.dv1step;
        data->fdata.texsw = tmp.t[0].w + (y + 0.5f - tmp.v[0].y) * data->fdata.dw1step;
        data->fdata.texeu = tmp.t[0].u + (y + 0.5f - tmp.v[0].y) * data->fdata.du2step;
        data->fdata.texev = tmp.t[0].v + (y + 0.5f - tmp.v[0].y) * data->fdata.dv2step;
        data->fdata.texew = tmp.t[0].w + (y + 0.5f - tmp.v[0].y) * data->fdata.dw2step;
        filltriangle(data, tmp, y);
    }
}

static void			flattop(t_cube *data, t_triangle tmp)
{
    int	    y;
    int     end;

    y = (int)ceil(tmp.v[0].y - 0.5f) - 1;
    end = (int)ceil(tmp.v[2].y - 0.5f);
    // data->fdata.left = tmp.t[0];
    // data->fdata.right = tmp.t[1];
    // data->fdata.bot = tmp.t[2];

    // data->fdata.stepl = texstep(data->fdata.bot, data->fdata.left, tmp.v[2].y - tmp.v[0].y);
    // data->fdata.stepr = texstep(data->fdata.bot, data->fdata.right, tmp.v[2].y - tmp.v[1].y);
    // data->fdata.left = texcoord(data->fdata.left, data->fdata.stepl, (float)y + 0.5f + 1 - tmp.v[1].y);
    // data->fdata.right = texcoord(data->fdata.right, data->fdata.stepr, (float)y + 0.5f + 1 - tmp.v[1].y);

    data->fdata.du1 = tmp.t[2].u - tmp.t[0].u;
    data->fdata.dv1 = tmp.t[2].v - tmp.t[0].v;
    data->fdata.dw1 = tmp.t[2].w - tmp.t[0].w;
    data->fdata.dx1 = tmp.v[2].x - tmp.v[0].x;
    data->fdata.dy1 = tmp.v[2].y - tmp.v[0].y;
    data->fdata.du2 = tmp.t[2].u - tmp.t[1].u;
    data->fdata.dv2 = tmp.t[2].v - tmp.t[1].v;
    data->fdata.dw2 = tmp.t[2].w - tmp.t[1].w;
    data->fdata.dx2 = tmp.v[2].x - tmp.v[1].x;
    data->fdata.dy2 = tmp.v[2].y - tmp.v[1].y;
    init_step(data);
    data->fdata.daxstep = (tmp.v[2].x - tmp.v[0].x) / (tmp.v[2].y - tmp.v[0].y);
    data->fdata.dbxstep = (tmp.v[2].x - tmp.v[1].x) / (tmp.v[2].y - tmp.v[1].y);
    while (++y < end)
    {
        // data->fdata.left = texcoord(data->fdata.left, data->fdata.stepl, 1);
        // data->fdata.right = texcoord(data->fdata.right, data->fdata.stepr, 1);
        data->fdata.ax = tmp.v[0].x + (y + 0.5f - tmp.v[0].y) * data->fdata.daxstep;
        data->fdata.bx = tmp.v[1].x + (y + 0.5f - tmp.v[1].y) * data->fdata.dbxstep;
        data->fdata.texsu = tmp.t[0].u + (y + 0.5f - tmp.v[0].y) * data->fdata.du1step;
        data->fdata.texsv = tmp.t[0].v + (y + 0.5f - tmp.v[0].y) * data->fdata.dv1step;
        data->fdata.texsw = tmp.t[0].w + (y + 0.5f - tmp.v[0].y) * data->fdata.dw1step;
        data->fdata.texeu = tmp.t[1].u + (y + 0.5f - tmp.v[1].y) * data->fdata.du2step;
        data->fdata.texev = tmp.t[1].v + (y + 0.5f - tmp.v[1].y) * data->fdata.dv2step;
        data->fdata.texew = tmp.t[1].w + (y + 0.5f - tmp.v[1].y) * data->fdata.dw2step;
        filltriangle(data, tmp, y);

    }
}

static void			general(t_cube *data, t_triangle tmp)
{
    float	alpha;
    t_vec2d ti;
    t_vec3d	vi;
    t_triangle triangle;

    alpha = (tmp.v[1].y - tmp.v[0].y) / (tmp.v[2].y - tmp.v[0].y);
    vi.x = ft_interpol(tmp.v[0].x, tmp.v[2].x, alpha);
    vi.y = ft_interpol(tmp.v[0].y, tmp.v[2].y, alpha);
    ti.u = ft_interpol(tmp.t[0].u, tmp.t[2].u, alpha);
    ti.v = ft_interpol(tmp.t[0].v, tmp.t[2].v, alpha);
    triangle = tmp;
    if (tmp.v[1].x < vi.x)
    {
        triangle.v[0] = tmp.v[0];
        triangle.t[0] = tmp.t[0];
        triangle.v[1] = tmp.v[1];
        triangle.t[1] = tmp.t[1];
        triangle.v[2] = vi;
        triangle.t[2] = ti;
        flatbot(data, triangle);
        triangle.v[0] = tmp.v[1];
        triangle.t[0] = tmp.t[1];
        triangle.v[1] = vi;
        triangle.t[1] = ti;
        triangle.v[2] = tmp.v[2];
        triangle.t[2] = tmp.t[2];
        flattop(data, triangle);
    }
    else
    {
        triangle.v[0] = tmp.v[0];
        triangle.t[0] = tmp.t[0];
        triangle.v[1] = vi;
        triangle.t[1] = ti;
        triangle.v[2] = tmp.v[1];
        triangle.t[2] = tmp.t[1];
        flatbot(data, triangle);
        triangle.v[0] = vi;
        triangle.t[0] = ti;
        triangle.v[1] = tmp.v[1];
        triangle.t[1] = tmp.t[1];
        triangle.v[2] = tmp.v[2];
        triangle.t[2] = tmp.t[2];
        flattop(data, triangle);
    }
}

static void         swap_vertex(t_triangle *tmp)
{
    if (tmp->v[1].y < tmp->v[0].y)
    {
        ft_swap((void *)&tmp->v[0], (void *)&tmp->v[1]);
        ft_swap((void *)&tmp->t[0], (void *)&tmp->t[1]);
    }
    if (tmp->v[2].y < tmp->v[1].y)
    {
        ft_swap((void *)&tmp->v[1], (void *)&tmp->v[2]);
        ft_swap((void *)&tmp->t[1], (void *)&tmp->t[2]);
    }
    if (tmp->v[1].y < tmp->v[0].y)
    {
        ft_swap((void *)&tmp->v[0], (void *)&tmp->v[1]);
        ft_swap((void *)&tmp->t[0], (void *)&tmp->t[1]);
    }
}

void				filltriangletomato(t_cube *data, t_triangle triangle)
{
    t_triangle  tmp;

    tmp = triangle;
    swap_vertex(&tmp);
    if (tmp.v[0].y == tmp.v[1].y)
    {
        if (tmp.v[1].x < tmp.v[0].x)
        {
            ft_swap((void *)&tmp.v[0], (void *)&tmp.v[1]);
            ft_swap((void *)&tmp.t[0], (void *)&tmp.t[1]);
        }
        flattop(data, tmp);
    }
    else if (tmp.v[1].y == tmp.v[2].y)
    {
        if (tmp.v[2].x < tmp.v[1].x)
        {
            ft_swap((void *)&tmp.v[1], (void *)&tmp.v[2]);
            ft_swap((void *)&tmp.t[1], (void *)&tmp.t[2]);
        }
        flatbot(data, tmp);
    }
    else
    	general(data, tmp);
}
