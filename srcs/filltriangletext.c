/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/21 21:37:02 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void     init_toptriangle(t_doom *data, t_triangle tmp)
{
    data->fdata.x1 = tmp.v[1].x - tmp.v[0].x;
    data->fdata.x2 = tmp.v[2].x - tmp.v[0].x;
    data->fdata.y1 = tmp.v[1].y - tmp.v[0].y;
    data->fdata.y2 = tmp.v[2].y - tmp.v[0].y;
    data->fdata.w1 = tmp.t[1].w - tmp.t[0].w;
    data->fdata.w2 = tmp.t[2].w - tmp.t[0].w;
    if (data->var.texture)
    {
        data->fdata.u1 = tmp.t[1].u - tmp.t[0].u;
        data->fdata.v1 = tmp.t[1].v - tmp.t[0].v;
        data->fdata.u2 = tmp.t[2].u - tmp.t[0].u;
        data->fdata.v2 = tmp.t[2].v - tmp.t[0].v;
    }
}

static void     init_bottomtriangle(t_doom *data, t_triangle tmp)
{
    data->fdata.x1 = tmp.v[2].x - tmp.v[1].x;
    data->fdata.y1 = tmp.v[2].y - tmp.v[1].y;
    data->fdata.w1 = tmp.t[2].w - tmp.t[1].w;
    if (data->var.texture)
    {
        data->fdata.u1 = tmp.t[2].u - tmp.t[1].u;
        data->fdata.v1 = tmp.t[2].v - tmp.t[1].v;
    }
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

void			filltriangletext(t_doom *data, t_triangle triangle)
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
