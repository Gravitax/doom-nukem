/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliptriangle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:46:36 by maboye            #+#    #+#             */
/*   Updated: 2020/02/03 16:50:54 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void     output_one(t_cube *data)
{
    data->cdata.out[0].v[0] = data->cdata.ipoints[0];
    data->cdata.out[0].t[0] = data->cdata.itex[0];
    data->cdata.out[0].v[1] = vecintersectplane(data,
        data->cdata.ipoints[0], data->cdata.opoints[0]);
    data->cdata.out[0].t[1].u = data->t * (data->cdata.otex[0].u
        - data->cdata.itex[0].u) + data->cdata.itex[0].u;
    data->cdata.out[0].t[1].v = data->t * (data->cdata.otex[0].v
        - data->cdata.itex[0].v) + data->cdata.itex[0].v;
    data->cdata.out[0].t[1].w = data->t * (data->cdata.otex[0].w
        - data->cdata.itex[0].w) + data->cdata.itex[0].w;
    data->cdata.out[0].v[2] = vecintersectplane(data,
        data->cdata.ipoints[0], data->cdata.opoints[1]);
    data->cdata.out[0].t[2].u = data->t * (data->cdata.otex[1].u
        - data->cdata.itex[0].u) + data->cdata.itex[0].u;
    data->cdata.out[0].t[2].v = data->t * (data->cdata.otex[1].v
        - data->cdata.itex[0].v) + data->cdata.itex[0].v;
    data->cdata.out[0].t[2].w = data->t * (data->cdata.otex[1].w
        - data->cdata.itex[0].w) + data->cdata.itex[0].w;
}

static void     output_two(t_cube *data)
{
    data->cdata.out[0].v[0] = data->cdata.ipoints[0];
    data->cdata.out[0].t[0] = data->cdata.itex[0];
    data->cdata.out[0].v[1] = data->cdata.ipoints[1];
    data->cdata.out[0].t[1] = data->cdata.itex[1];
    data->cdata.out[0].v[2] = vecintersectplane(data,
        data->cdata.ipoints[0], data->cdata.opoints[0]);
    data->cdata.out[0].t[2].u = data->t * (data->cdata.otex[0].u
        - data->cdata.itex[0].u) + data->cdata.itex[0].u;
    data->cdata.out[0].t[2].v = data->t * (data->cdata.otex[0].v
        - data->cdata.itex[0].v) + data->cdata.itex[0].v;
    data->cdata.out[0].t[2].w = data->t * (data->cdata.otex[0].w
        - data->cdata.itex[0].w) + data->cdata.itex[0].w;

    data->cdata.out[1].v[0] = data->cdata.ipoints[1];
    data->cdata.out[1].t[0] = data->cdata.itex[1];
    data->cdata.out[1].v[1] = data->cdata.out[0].v[2];
    data->cdata.out[1].t[1] = data->cdata.out[0].t[2];
    data->cdata.out[1].v[2] = vecintersectplane(data,
        data->cdata.ipoints[1], data->cdata.opoints[0]);
    data->cdata.out[1].t[2].u = data->t * (data->cdata.otex[0].u
        - data->cdata.itex[1].u) + data->cdata.itex[1].u;
    data->cdata.out[1].t[2].v = data->t * (data->cdata.otex[0].v
        - data->cdata.itex[1].v) + data->cdata.itex[1].v;
    data->cdata.out[1].t[2].w = data->t * (data->cdata.otex[0].w
        - data->cdata.itex[1].w) + data->cdata.itex[1].w;
}

int             newtriangles(t_cube *data)
{
    t_triangle  tmp;

    if (data->cdata.inside == 1 && data->cdata.outside == 2)
    {
        output_one(data);
        data->cdata.out[0].color = 0xff00ffff;
        return (1);
    }
    else if (data->cdata.inside == 2 && data->cdata.outside == 1)
    {
        output_two(data);
        data->cdata.out[0].color = 0xf00fff55;
        data->cdata.out[1].color = 0xffff00ff;
        return (2);
    }
    else
	    return (0);
}
