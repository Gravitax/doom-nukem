/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cliptriangle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:46:36 by maboye            #+#    #+#             */
/*   Updated: 2020/02/12 15:51:04 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_vec2d         textinterpol(t_vec2d v1, t_vec2d v2, float alpha)
{
    return ((t_vec2d){ ft_interpol(v1.u, v2.u, alpha),
        ft_interpol(v1.v, v2.v, alpha),
        ft_interpol(v1.w, v2.w, alpha) });
}

static void     output_one(t_doom *data)
{
    data->cdata.out[0].v[0] = data->cdata.ipoints[0];
    data->cdata.out[0].t[0] = data->cdata.itex[0];
    data->cdata.out[0].v[1] = vecintersectplane(data,
        data->cdata.ipoints[0], data->cdata.opoints[0]);
    data->cdata.out[0].t[1] = textinterpol(data->cdata.itex[0],
        data->cdata.otex[0], data->var.t);
    data->cdata.out[0].v[2] = vecintersectplane(data,
        data->cdata.ipoints[0], data->cdata.opoints[1]);
    data->cdata.out[0].t[2] = textinterpol(data->cdata.itex[0],
        data->cdata.otex[1], data->var.t);
}

static void     output_two(t_doom *data)
{
    data->cdata.out[0].v[0] = data->cdata.ipoints[0];
    data->cdata.out[0].t[0] = data->cdata.itex[0];
    data->cdata.out[0].v[1] = data->cdata.ipoints[1];
    data->cdata.out[0].t[1] = data->cdata.itex[1];
    data->cdata.out[0].v[2] = vecintersectplane(data,
        data->cdata.ipoints[0], data->cdata.opoints[0]);
    data->cdata.out[0].t[2] = textinterpol(data->cdata.itex[0],
        data->cdata.otex[0], data->var.t);
    data->cdata.out[1].v[0] = data->cdata.ipoints[1];
    data->cdata.out[1].t[0] = data->cdata.itex[1];
    data->cdata.out[1].v[1] = data->cdata.out[0].v[2];
    data->cdata.out[1].t[1] = data->cdata.out[0].t[2];
    data->cdata.out[1].v[2] = vecintersectplane(data,
        data->cdata.ipoints[1], data->cdata.opoints[0]);
    data->cdata.out[1].t[2] = textinterpol(data->cdata.itex[1],
        data->cdata.otex[0], data->var.t);
}

int             newtriangles(t_doom *data)
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
