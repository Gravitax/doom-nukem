/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliptriangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/01/29 16:55:26 by maboye           ###   ########.fr       */
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

static void     test_vertex(t_cube *data, t_vec3d vertex, t_vec2d texture)
{
    if (vecdist(data, vertex) >= 0)
    {
        data->cdata.ipoints[data->cdata.inside] = vertex;
        data->cdata.itex[data->cdata.inside++] = texture;
    }
    else
    {
        data->cdata.opoints[data->cdata.outside] = vertex;
        data->cdata.otex[data->cdata.outside++] = texture;
    }   
}

int             cliptriangle(t_cube *data)
{
    data->cdata.nplane = vecnormalise(data->cdata.nplane);
    data->cdata.inside = 0;
    data->cdata.outside = 0;
    data->cdata.out[0].color = data->cdata.in.color;
    data->cdata.out[1].color = data->cdata.in.color;
    test_vertex(data, data->cdata.in.v[0], data->cdata.in.t[0]);
    test_vertex(data, data->cdata.in.v[1], data->cdata.in.t[1]);
    test_vertex(data, data->cdata.in.v[2], data->cdata.in.t[2]);
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
