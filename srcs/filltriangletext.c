/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filltriangletext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/03 21:10:27 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     init_toptriangle(t_cube *data, t_triangle tmp)
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
}

static void     init_bottomtriangle(t_cube *data, t_triangle tmp)
{
    data->fdata.du1 = tmp.t[2].u - tmp.t[1].u;
    data->fdata.dv1 = tmp.t[2].v - tmp.t[1].v;
    data->fdata.dw1 = tmp.t[2].w - tmp.t[1].w;
    data->fdata.dx1 = tmp.v[2].x - tmp.v[1].x;
    data->fdata.dy1 = tmp.v[2].y - tmp.v[1].y;
}

static void     swap_vertex(t_triangle *tmp)
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

void			filltriangletext(t_cube *data, t_triangle triangle)
{
    t_triangle  tmp;

    tmp = triangle;
    swap_vertex(&tmp);
    init_toptriangle(data, tmp);
	if (data->fdata.dy1)
        fill_top(data, tmp);
    init_bottomtriangle(data, tmp);
	if (data->fdata.dy1)
        fill_bottom(data, tmp);
}
