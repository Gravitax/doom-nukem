/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliptriangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2019/12/16 16:09:32 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

#include "../includes/cube3d.h"

static float    vecdist(t_cube *data, t_vec3d p)
{
    return (data->cdata.nplane.x * p.x
        + data->cdata.nplane.y * p.y
        + data->cdata.nplane.z * p.z
        - vecdotproduct(data->cdata.nplane, data->cdata.pplane));
}

static void     test_vertex(t_cube *data)
{
    if (vecdist(data, data->cdata.in.v[0]) >= 0)
    {
        data->cdata.ipoints[data->cdata.inside++] = data->cdata.in.v[0];
        data->cdata.itex[data->cdata.it++] = data->cdata.in.t[0];
    }
    else
    {
        data->cdata.opoints[data->cdata.outside++] = data->cdata.in.v[0];
        data->cdata.otex[data->cdata.ot++] = data->cdata.in.t[0];
    }
    if (vecdist(data, data->cdata.in.v[1]) >= 0)
    {
        data->cdata.ipoints[data->cdata.inside++] = data->cdata.in.v[1];
        data->cdata.itex[data->cdata.it++] = data->cdata.in.t[1];
    }
    else
    {
        data->cdata.opoints[data->cdata.outside++] = data->cdata.in.v[1];
        data->cdata.otex[data->cdata.ot++] = data->cdata.in.t[1];
    }
    if (vecdist(data, data->cdata.in.v[2]) >= 0)
    {
        data->cdata.ipoints[data->cdata.inside++] = data->cdata.in.v[2];
        data->cdata.itex[data->cdata.it++] = data->cdata.in.t[2];
    }
    else
    {
        data->cdata.opoints[data->cdata.outside++] = data->cdata.in.v[2];
        data->cdata.otex[data->cdata.ot++] = data->cdata.in.t[2];
    }
}

static int      newtriangles(t_cube *data)
{
    if (data->cdata.inside == 1 && data->cdata.outside == 2)
    {
        data->cdata.out[0].v[0] = data->cdata.ipoints[0];
        data->cdata.out[0].t[0] = data->cdata.itex[0];

        data->cdata.out[0].v[1] = vecintersectplane(data,
            data->cdata.ipoints[0], data->cdata.opoints[0]);
        data->cdata.out[0].t[1].u = data->cdata.itex[0].u + data->t
            * (data->cdata.otex[0].u - data->cdata.itex[0].u);
        data->cdata.out[0].t[1].v = data->cdata.itex[0].v + data->t
            * (data->cdata.otex[0].v - data->cdata.itex[0].v);
        data->cdata.out[0].t[1].w = data->cdata.itex[0].w + data->t
            * (data->cdata.otex[0].w - data->cdata.itex[0].w);

        data->cdata.out[0].v[2] = vecintersectplane(data,
            data->cdata.ipoints[0], data->cdata.opoints[1]);
        data->cdata.out[0].t[2].u = data->cdata.itex[0].u + data->t
            * (data->cdata.otex[1].u - data->cdata.itex[0].u);
        data->cdata.out[0].t[2].v = data->cdata.itex[0].v + data->t
            * (data->cdata.otex[1].v - data->cdata.itex[0].v);
        data->cdata.out[0].t[2].w = data->cdata.itex[0].w + data->t
            * (data->cdata.otex[1].w - data->cdata.itex[0].w);
        
        data->cdata.out[0].color = 0xff00ffff;
        return (1);
    }
    else if (data->cdata.inside == 2 && data->cdata.outside == 1)
    {
        data->cdata.out[0].v[0] = data->cdata.ipoints[0];
        data->cdata.out[0].v[1] = data->cdata.ipoints[1];
        data->cdata.out[0].t[0] = data->cdata.itex[0];
        data->cdata.out[0].t[1] = data->cdata.itex[1];
        data->cdata.out[0].v[2] = vecintersectplane(data,
            data->cdata.ipoints[0], data->cdata.opoints[0]);
        data->cdata.out[0].t[2].u = data->cdata.itex[0].u + data->t
            * (data->cdata.otex[0].u - data->cdata.itex[0].u);
        data->cdata.out[0].t[2].v = data->cdata.itex[0].v + data->t
            * (data->cdata.otex[0].v - data->cdata.itex[0].v);
        data->cdata.out[0].t[2].w = data->cdata.itex[0].w + data->t
            * (data->cdata.otex[0].w - data->cdata.itex[0].w);
        data->cdata.out[0].color = 0xf00fff55;

        data->cdata.out[1].v[0] = data->cdata.ipoints[1];
        data->cdata.out[1].t[0] = data->cdata.itex[1];
        data->cdata.out[1].v[1] = data->cdata.out[0].v[2];
        data->cdata.out[1].t[1] = data->cdata.out[0].t[2];
        data->cdata.out[1].v[2] = vecintersectplane(data,
            data->cdata.ipoints[1], data->cdata.opoints[0]);
        data->cdata.out[0].t[2].u = data->cdata.itex[1].u + data->t
            * (data->cdata.otex[0].u - data->cdata.itex[1].u);
        data->cdata.out[0].t[2].v = data->cdata.itex[1].v + data->t
            * (data->cdata.otex[0].v - data->cdata.itex[1].v);
        data->cdata.out[0].t[2].w = data->cdata.itex[1].w + data->t
            * (data->cdata.otex[0].w - data->cdata.itex[1].w);
        data->cdata.out[1].color = 0xffff00ff;
        return (2);
    }
	return (0);
}

int             cliptriangle(t_cube *data)
{
    data->cdata.nplane = vecnormalise(data->cdata.nplane);
    data->cdata.inside = 0;
    data->cdata.outside = 0;
    data->cdata.it = 0;
    data->cdata.ot = 0;
    data->cdata.out[0].color = data->cdata.in.color;
    data->cdata.out[1].color = data->cdata.in.color;
    test_vertex(data);
    if (data->cdata.inside == 0)
        return (0);
    else if (data->cdata.inside == 3)
    {
        data->cdata.out[0] = data->cdata.in;
        return (1);
    }
    else
        return (newtriangles(data));
}
