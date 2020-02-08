/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/08 01:15:47 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     init_toptriangle(t_cube *data, t_triangle tmp)
{
    data->fdata.u1 = tmp.t[1].u - tmp.t[0].u;
    data->fdata.v1 = tmp.t[1].v - tmp.t[0].v;
    data->fdata.w1 = tmp.t[1].w - tmp.t[0].w;
    data->fdata.x1 = tmp.v[1].x - tmp.v[0].x;
    data->fdata.y1 = tmp.v[1].y - tmp.v[0].y;
    data->fdata.u2 = tmp.t[2].u - tmp.t[0].u;
    data->fdata.v2 = tmp.t[2].v - tmp.t[0].v;
    data->fdata.w2 = tmp.t[2].w - tmp.t[0].w;
    data->fdata.x2 = tmp.v[2].x - tmp.v[0].x;
    data->fdata.y2 = tmp.v[2].y - tmp.v[0].y;
}

static void     init_bottomtriangle(t_cube *data, t_triangle tmp)
{
    data->fdata.u1 = tmp.t[2].u - tmp.t[1].u;
    data->fdata.v1 = tmp.t[2].v - tmp.t[1].v;
    data->fdata.w1 = tmp.t[2].w - tmp.t[1].w;
    data->fdata.x1 = tmp.v[2].x - tmp.v[1].x;
    data->fdata.y1 = tmp.v[2].y - tmp.v[1].y;
}

static void     swap_vertex(t_triangle *tmp)
{
	if (tmp->v[1].y < tmp->v[0].y)
	{
		swap_floats(&tmp->t[0].u, &tmp->t[1].u);
		swap_floats(&tmp->t[0].v, &tmp->t[1].v);
        swap_floats(&tmp->t[0].w, &tmp->t[1].w);
		swap_floats(&tmp->v[0].x, &tmp->v[1].x);
		swap_floats(&tmp->v[0].y, &tmp->v[1].y);
	}
	if (tmp->v[2].y < tmp->v[1].y)
	{
		swap_floats(&tmp->t[1].u, &tmp->t[2].u);
		swap_floats(&tmp->t[1].v, &tmp->t[2].v);
        swap_floats(&tmp->t[1].w, &tmp->t[2].w);
		swap_floats(&tmp->v[1].x, &tmp->v[2].x);
		swap_floats(&tmp->v[1].y, &tmp->v[2].y);
	}
	if (tmp->v[1].y < tmp->v[0].y)
	{
		swap_floats(&tmp->t[0].u, &tmp->t[1].u);
		swap_floats(&tmp->t[0].v, &tmp->t[1].v);
        swap_floats(&tmp->t[0].w, &tmp->t[1].w);
		swap_floats(&tmp->v[0].x, &tmp->v[1].x);
		swap_floats(&tmp->v[0].y, &tmp->v[1].y);
	}
}

void			filltriangletext(t_cube *data, t_triangle triangle)
{
    t_triangle  tmp;

    data->var.color = triangle.color;
    tmp = triangle;
    swap_vertex(&tmp);
    init_toptriangle(data, tmp);
	if (data->fdata.y1)
        fill_top(data, tmp);
    init_bottomtriangle(data, tmp);
	if (data->fdata.y1)
        fill_bottom(data, tmp);
}
