/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliptriangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by maboye            #+#    #+#             */
/*   Updated: 2020/02/03 17:06:40 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static int      inside_plane(t_cube *data, t_vec3d p)
{
    return (vecdotproduct(data->cdata.nplane, data->cdata.pplane)
        - vecdotproduct(data->cdata.nplane, p) < 0);
}

static void     test_vertex(t_cube *data, t_vec3d vertex, t_vec2d texture)
{
    if (inside_plane(data, vertex))
    {
        data->cdata.ipoints[data->cdata.inside] = vertex;
        data->cdata.itex[data->cdata.inside] = texture;
        ++data->cdata.inside;
    }
    else
    {
        data->cdata.opoints[data->cdata.outside] = vertex;
        data->cdata.otex[data->cdata.outside] = texture;
        ++data->cdata.outside;
    }   
}

int             cliptriangle(t_cube *data)
{
    int i;

    data->cdata.inside = 0;
    data->cdata.outside = 0;
    data->cdata.out[0] = data->cdata.in;
    data->cdata.out[1] = data->cdata.in;
    i = -1;
    while (++i < 3)
    {
        if (data->cdata.in.v[i].z > 16)
        {
            //printf("z: %f\n", data->cdata.in.v[i].z);
            return (0);
        }
        test_vertex(data, data->cdata.in.v[i], data->cdata.in.t[i]);
    }
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
